import ui.WindowApp
import java.awt.EventQueue

fun createAndShowGUI()
{
    val frame = WindowApp("Моделирование, ЛР2, Якуба Дмитрий, ИУ7-73Б")
    frame.isVisible = true
}

fun main()
{
    EventQueue.invokeLater(::createAndShowGUI)
}