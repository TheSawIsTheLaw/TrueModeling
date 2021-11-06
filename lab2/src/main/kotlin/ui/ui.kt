package ui

import java.awt.GridLayout
import javax.swing.JFrame
import javax.swing.UIManager

class WindowApp(title: String): JFrame()
{
    private fun createUI(title: String)
    {
        setTitle(title)
        try
        {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel")
        } catch (exc: Exception)
        {
            UIManager.setLookAndFeel("com.sun.java.swing.plaf.gtk.GTKLookAndFeel")
        }
        defaultCloseOperation = EXIT_ON_CLOSE
        setSize(800, 165)
        layout = GridLayout(1, 1)

        setLocationRelativeTo(null)
    }

    init
    {
        createUI(title)
    }
}