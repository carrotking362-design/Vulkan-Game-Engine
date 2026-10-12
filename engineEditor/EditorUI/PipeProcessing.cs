
using Avalonia.Controls;

namespace EditorUI
{
    public static class PipeProcessing
    {
        private static TextBlock? fpsCounter;
        public static void SetFpsUI(TextBlock t)
        {
            fpsCounter = t;
        }
        public static void UpdateFps(int fps)
        {
            Console.Log("New FPS: " + fps);
            if(fpsCounter != null)
                fpsCounter.Text = $"FPS: {fps}";
            else
                Console.Error("FpsCounter UI object is Null");
        }
    }
}