// This file is just a layer between the actual UI and the Editor UI backend,
//
//      It passes button clicks through into the EditorUI namespace
//      It will also take data from EditorUI for updating UI


using Avalonia.Controls;
using Avalonia.Interactivity;
using EditorUI.Piping;

namespace EngineEditor;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();

        InitializeEditorUI();
    }

    public void InitializeEditorUI()
    {
        EditorUI.Console.SetTarget(ConsoleOutput);
        InitializeLinks();
    }

    public void InitializeLinks()
    {
        TopProjectButton.Click += HeaderProjectButtonClicked;

        ViewportPlay.Click += EditorUI.Runtime.Play;
        ViewportPause.Click += EditorUI.Runtime.Pause;
        ViewportNew.Click += EditorUI.Runtime.NewInstance;

        EditorUI.PipeProcessing.SetFpsUI(FpsCounter);
    }

    public void HeaderProjectButtonClicked(object? sender, RoutedEventArgs e)
    {
        EditorUI.Console.Log("Requesting FPS Update..");
        Pipe.Send((byte)EditorUI.Piping.Enums.Header.Engine, (byte)EditorUI.Piping.Enums.EngineCommand.GetFps, []);
    }
}
