using Avalonia.Controls;
using Avalonia.Media;


namespace EditorUI
{

    public static class Console
    {
        private static StackPanel? console = null;
        public static SolidColorBrush GetColor(byte r, byte g, byte b)
        {
            return new SolidColorBrush(Color.FromRgb(r,g,b));
        }
        public static void SetTarget(StackPanel _console)
        {
            console = _console;
        }
        public static void writeRaw(string message)
        {
            TextBlock text = new TextBlock();
            text.Classes.Add("monospace");
            text.Text = message;
            text.Foreground = GetColor(255,255,255);

            console.Children.Add(text);

            System.Console.WriteLine(message);
        }
        public static void writeColor(string message, SolidColorBrush color)
        {
            TextBlock text = new TextBlock();
            text.Classes.Add("monospace");
            text.Text = message;
            text.Foreground = color;

            console.Children.Add(text);

            System.Console.WriteLine(message);
        }
        public static void Log(string message)
        {
            writeColor($"[  LOG  ] {message}", GetColor(255,255,255));
        }
        public static void Warn(string message)
        {
            writeColor($"[WARNING] {message}", GetColor(255,219,88));
        }
        public static void Error(string message)
        {
            writeColor($"[ ERROR ] {message}", GetColor(205,28,24));
        }
    }    
}