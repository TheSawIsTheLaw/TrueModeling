package ui
import java.awt.*
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

    private fun prepareAndPlaceParametersPanel()
    {
        val parametersPanel = JPanel()
        parametersPanel.border = BorderFactory.createTitledBorder("Распределение и параметры")
        val firstParameterLabel = makeJLabel(pairOfEvenDistributionParameters.first)
        parametersPanel.add(firstParameterLabel)
        parametersPanel.add(makeJInput())
        val secondParameterLabel = makeJLabel(pairOfEvenDistributionParameters.second)
        parametersPanel.add(secondParameterLabel)
        parametersPanel.add(makeJInput())
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
        parametersPanel.add(makeJButton(textForGoButton))

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
        layout = GridLayout(3, 1)

        setLocationRelativeTo(null)

        prepareAndPlaceParametersPanel()

        prepareAndPlacePlotDistributionPanel()

        prepareAndPlacePlotDensityPanel()
    }
}