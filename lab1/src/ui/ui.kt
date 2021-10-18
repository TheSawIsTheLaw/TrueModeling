package ui

import org.jfree.chart.ChartFactory
import org.jfree.chart.ChartPanel
import org.jfree.chart.plot.PlotOrientation
import org.jfree.data.xy.XYDataset
import org.jfree.data.xy.XYSeries
import org.jfree.data.xy.XYSeriesCollection
import java.awt.*
import java.lang.NumberFormatException
import javax.swing.*

class DistributionWindowApp(title: String) : JFrame()
{
    private val usedFont = Font("Comic Sans", Font.PLAIN, 16)
    private val sizeOfTextEdit = 10
    private val listOfUsedDistributions = listOf("Равномерное распределение", "Распределение Гаусса")
    private val textForGoButton = "Свершить предначертанное"

    private val pairOfEvenDistributionParameters = Pair("a = ", "b = ")
    private val pairOfGaussianDistributionParameters = Pair("μ = ", "σ = ")

    private lateinit var plotDistributionPanel: JPanel
    private lateinit var plotDensityPanel: JPanel

//    private val firstParameterLabel = makeJLabel(pairOfEvenDistributionParameters.first)
//    private val secondParameterLabel = makeJLabel(pairOfEvenDistributionParameters.second)

    init
    {
        createUI(title)
    }

    private fun makeJLabel(innerText: String): JLabel
    {
        val outLabel = JLabel()
        outLabel.text = innerText
        outLabel.font = usedFont

        return outLabel
    }

    private fun makeJInput(): JTextField
    {
        val outTextField = JTextField(sizeOfTextEdit)
        outTextField.font = usedFont

        return outTextField
    }

    private fun makeComboBoxWith(listOfElements: List<String>): JComboBox<String>
    {
        val outComboBox = JComboBox<String>()
        for (i in listOfElements)
        {
            outComboBox.addItem(i)
        }
        outComboBox.selectedIndex = 0
        outComboBox.font = usedFont

        return outComboBox
    }

    private fun makeJButton(innerText: String): JButton
    {
        val outButton = JButton(innerText)
        outButton.font = usedFont

        return outButton
    }

    private fun checkInputParameters(firstParameter: String, secondParameter: String): Boolean
    {
        try
        {
            firstParameter.toFloat()
            secondParameter.toFloat()
        } catch (exc: NumberFormatException)
        {
            return false
        }

        return true
    }

    private fun makeAndAddPlotsForEvenDistribution(parameterA_: Float, parameterB_: Float)
    {
        var parameterA = parameterA_
        var parameterB = parameterB_
        if (parameterA > parameterB)
        {
            parameterA = parameterB.also { parameterB = parameterA }
        }
        val sizeOfPlate = parameterB - parameterA
        val stepOnPlate = sizeOfPlate / 1e3
        var currentX = parameterA - sizeOfPlate / 3

        val distributionSeries = XYSeries("Функция распределения")
        val densitySeries = XYSeries("Плотность распределения")
        for (i in 0 until (5 * sizeOfPlate / (3 * stepOnPlate) + 1).toInt())
        {
            val curDistr = when
            {
                currentX < parameterA -> 0
                currentX > parameterB -> 1
                else                  -> (currentX - parameterA) / (parameterB - parameterA)
            }
            distributionSeries.add(currentX, curDistr)

            val curDensity = when (currentX)
            {
                in parameterA..parameterB -> 1 / (parameterB - parameterA)
                else                      -> 1
            }
            densitySeries.add(currentX, curDensity)

            currentX += stepOnPlate.toFloat()
        }

        ???.add(
            ChartPanel(ChartFactory.createXYLineChart(
                "Функция распределения",
                "x",
                "F(x)",
                XYSeriesCollection(distributionSeries),
                PlotOrientation.VERTICAL, true, true, false)))
        ???.add(ChartPanel(ChartFactory.createXYLineChart(
            "Функция плотности распределения",
            "x",
            "f(x)",
            XYSeriesCollection(densitySeries),
            PlotOrientation.VERTICAL, true, true, false)))
    }

    private fun prepareAndPlaceParametersPanel()
    {
        val parametersPanel = JPanel()
        parametersPanel.border = BorderFactory.createTitledBorder("Распределение и параметры")
        val firstParameterLabel = makeJLabel(pairOfEvenDistributionParameters.first)
        parametersPanel.add(firstParameterLabel)
        val firstInput = makeJInput()
        parametersPanel.add(firstInput)
        val secondParameterLabel = makeJLabel(pairOfEvenDistributionParameters.second)
        parametersPanel.add(secondParameterLabel)
        val secondInput = makeJInput()
        parametersPanel.add(secondInput)

        val distributionCombo = makeComboBoxWith(listOfUsedDistributions)
        distributionCombo.addActionListener {
            if (distributionCombo.selectedIndex == 1)
            {
                firstParameterLabel.text = pairOfGaussianDistributionParameters.first
                secondParameterLabel.text = pairOfGaussianDistributionParameters.second
            }
            else
            {
                firstParameterLabel.text = pairOfEvenDistributionParameters.first
                secondParameterLabel.text = pairOfEvenDistributionParameters.second
            }
        }
        parametersPanel.add(distributionCombo)

        val parent = this
        val goButton = makeJButton(textForGoButton)
        // Возможно стоит вынести графики в приваты, а после выполнения листенера подтягивать их в фрейм.
        goButton.addActionListener {
            if (checkInputParameters(firstInput.text, secondInput.text))
            {
                when (distributionCombo.selectedIndex)
                {
                    0 -> makeAndAddPlotsForEvenDistribution(firstInput.text.toFloat(), secondInput.text.toFloat())
                    1 -> TODO()
                }
            }
            else
            {
                val message =
                    JLabel(
                        "Переданные параметры не могут быть распознаны как вещественные числа. " +
                                "В качестве разделителя следует использовать точку."
                    )
                message.font = usedFont
                JOptionPane.showMessageDialog(
                    this,
                    message,
                    "Ошибка ввода",
                    JOptionPane.ERROR_MESSAGE
                )
            }
        }
        parametersPanel.add(goButton)

        this.add(parametersPanel)
    }

    private fun prepareAndPlacePlotDensityPanel()
    {
        val plotDensity = JPanel()
        plotDensity.border = BorderFactory.createTitledBorder("График плотности распределения")

        plotDensityPanel = plotDensity
        this.add(plotDensity)
    }

    private fun prepareAndPlacePlotDistributionPanel()
    {
        val plotDistributionFunction = JPanel()
        plotDistributionFunction.border = BorderFactory.createTitledBorder("График функции распределения")
        plotDistributionFunction.foreground = Color.GRAY

        plotDistributionPanel = plotDistributionFunction
        this.add(plotDistributionFunction)
    }

    private fun createUI(title: String)
    {
        setTitle(title)
        UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel")

        defaultCloseOperation = EXIT_ON_CLOSE
        setSize(800, 600)
        layout = GridLayout(3, 1)

        setLocationRelativeTo(null)

        prepareAndPlaceParametersPanel()

//        prepareAndPlacePlotDistributionPanel()
//
//        prepareAndPlacePlotDensityPanel()
    }
}