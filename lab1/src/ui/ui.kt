package ui

import java.awt.*
import java.awt.event.ActionListener
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

        val goButton = makeJButton(textForGoButton)
        goButton.addActionListener {
            if (checkInputParameters(firstInput.text, secondInput.text))
            {
                TODO("Build and add graphics")
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
        val plotDensityPanel = JPanel()
        plotDensityPanel.border = BorderFactory.createTitledBorder("График плотности распределения")

        this.add(plotDensityPanel)
    }

    private fun prepareAndPlacePlotDistributionPanel()
    {
        val plotDistributionFunction = JPanel()
        plotDistributionFunction.border = BorderFactory.createTitledBorder("График функции распределения")

        this.add(plotDistributionFunction)
    }

    private fun createUI(title: String)
    {
        setTitle(title)
        UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel")

        defaultCloseOperation = EXIT_ON_CLOSE
        setSize(800, 600)
        layout = GridLayout(1, 1)

        setLocationRelativeTo(null)

        prepareAndPlaceParametersPanel()

//        prepareAndPlacePlotDistributionPanel()
//
//        prepareAndPlacePlotDensityPanel()
    }
}