import wx
import cv2


class WindowClass (wx.Frame):

    def __init__(self, parent, title):
        super(WindowClass, self).__init__(parent, title=title, size=(800, 600))
        panel = wx.Panel(self)
        buttonnewp = wx.Button(panel, label="Novo Projeto", pos=(200, 200), size=(100, 30))
        buttonopenp = wx.Button(panel, label="Abrir Projeto", pos=(200, 235), size=(100, 30))
        buttonprojetos = wx.Button(panel, label="Projetos Antigos", pos=(200, 270), size=(100, 30))
        buttonconfig = wx.Button(panel, label="Configurações", pos=(200, 305), size=(100, 30))
        buttonnewp.BackgroundColour = (0, 180, 200)
        buttonconfig.BackgroundColour = (0, 180, 200)
        buttonopenp.BackgroundColour = (0, 180, 200)
        buttonprojetos.BackgroundColour = (0, 180, 200)
        self.Center()
        self.Show()

        status = self.CreateStatusBar()
        menubar = wx.MenuBar()
        primeiro = wx.Menu()
        segundo = wx.Menu()
        terceiro = wx.Menu()
        primeiro.Append(wx.NewId(), "Abrir...")
        terceiro.Append(wx.NewId(), "Sobre o programa")
        terceiro.Append(wx.NewId(), "Sobre os desenvolvedores")
        menubar.Append(primeiro, "Arquivo")
        menubar.Append(segundo, "configurações")
        menubar.Append(terceiro, "Help")
        self.SetMenuBar(menubar)


app = wx.App()
WindowClass(None, 'TCC')
cv2.waitKey()
app.MainLoop()

