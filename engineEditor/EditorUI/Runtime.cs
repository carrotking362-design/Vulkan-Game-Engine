using Avalonia.Interactivity;

using System.Diagnostics;
using System.IO;

using EditorUI.Piping;
using EditorUI.Piping.Enums;
using System;

namespace EditorUI
{
    /// <summary>
    /// Manages the C++ Engines runtime (responsible for Play/Pause)
    /// </summary>
    public static class Runtime
    {
        private static bool hasInstance = false;
        public static void Play(object? sender, RoutedEventArgs? e)
        {
            if (!hasInstance)
            {
                NewInstance(null, null);
            }

            Console.Log("Playing Engine");
            Pipe.Send((byte)Header.Engine, (byte)EngineCommand.Play, []);
        }

        public static void Pause(object? sender, RoutedEventArgs? e)
        {
            Console.Log("Paused Engine");
            Pipe.Send((byte)Header.Engine, (byte)EngineCommand.Pause, []);
        }

        public static void SetFps(int fps)
        {
            Console.Log("Set Fps of Engine");
            Pipe.Send((byte)Header.Engine, (byte)EngineCommand.SetFps, [..BitConverter.GetBytes(fps)]);
        }

        public static void GetFps()
        {
            Console.Log("Set Fps of Engine");
            Pipe.Send((byte)Header.Engine, (byte)EngineCommand.GetFps, []);
        }

        public static void ReloadScene()
        {
            
        }

        public static void NewInstance(object? sender, RoutedEventArgs? e)
        {
            hasInstance = true;


            Pipe.MakePipe();

            string exePath = "main.exe";

            var psi = new ProcessStartInfo
            {
                FileName = exePath,
                WorkingDirectory = Path.GetDirectoryName(exePath),
                UseShellExecute = false,
                CreateNoWindow = false
            };

            Process? engineProcess = Process.Start(psi);

            Console.Log("Engine Started");
        }
    }
}