import ui.DistributionWindowApp

import java.awt.EventQueue

fun createAndShowGUI()
{

    val frame = DistributionWindowApp("Моделирование. ЛР1, Якуба Дмитрий, ИУ7-73Б")
    frame.isVisible = true
}

fun main()
{
    EventQueue.invokeLater(::createAndShowGUI)
}