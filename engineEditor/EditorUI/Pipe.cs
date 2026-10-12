using System;
using System.IO;
using System.IO.Pipes;

using EditorUI.Piping.Enums;

namespace EditorUI
{
    namespace Piping
    {
        /// <summary>
        /// Manages all communication between the C# UI and the C++ Engine Core
        /// </summary>
        public static class Pipe
        {
            private static NamedPipeServerStream? server;
            private static BinaryReader? reader;
            
            private static bool pipeConnected = false;

            public static void MakePipe()
            {
                if(server != null)
                {
                    Console.Warn("Server isnt null! Replacing with a new named pipe name!");
                }

                pipeConnected = false;
                server = new NamedPipeServerStream("EasyEditor0", PipeDirection.InOut, 1, PipeTransmissionMode.Byte);
                reader = new BinaryReader(server);

                Console.Log("Pipe Server Created");

                server.WaitForConnectionAsync();

                Console.Log("Pipe Server Connected!");
                pipeConnected = true;
            }

            public static void SendRaw(byte[] payload)
            {
                if(payload.Length > 1)
                {
                    Send(payload[0], payload[1], payload[2..]);
                }
                else
                {
                    Console.Log("Pipe.SendRaw(): payload too short to be used!");
                } 
            }

            public static void Send(byte header, byte command, byte[] args)
            {
                if (!pipeConnected)
                {
                    Console.Warn("failed to send data: Pipe isnt connected");
                    return;
                }
                try
                {
                    using var ms = new MemoryStream();
                    using (var bw = new BinaryWriter(ms, System.Text.Encoding.UTF8, leaveOpen: true))
                    {
                        bw.Write(header);
                        bw.Write(command);
                        bw.Write(args.Length);
                        bw.Write(args);
                    };

                    if(server == null)
                    {
                        throw new Exception("'server' variable is null. Please run 'Pipe.MakeNew()' with or without a pipe name to ensure the server isnt null");
                    }

                    server.Write(ms.GetBuffer(), 0, (int)ms.Length);
                    server.Flush();

                    Console.Log("Send Data to C++ Engine..");

                    int rLength = reader.ReadInt32();
                    
                    HandleRawBytes(reader.ReadBytes(rLength));
                }
                catch(Exception e)
                {
                    Console.Log("Error when sending bytes to C++ Engine:\n\t" + e.Message);
                }
            }
            public static void HandleRawBytes(byte[] recieved)
            {
                if(recieved.Length > 1)
                {
                    HandleBytes(recieved[0], recieved[1], recieved[2..]);
                }
                else
                {
                    Console.Log("Recieved bytes are too short to be used as a response.");
                }
            }
            public static void HandleBytes(byte header, byte command, byte[] args)
            {
                switch ((Header)header)
                {
                    case Header.Null:
                        Console.Log("Null byte recieved");
                        break;

                    case Header.Error:
                        Console.Log("Error occured");
                        break;

                    case Header.Engine:
                        HandleEngine(command, args);
                        break;
                    case Header.Renderer:
                        HandleRenderer(command, args);
                        break;
                    case Header.Scene:
                        HandleScene(command, args);
                        break;
                }
            }


            private static void HandleEngine(byte command, byte[] args)
            {
                switch ((EngineCommand)command)
                {
                    case EngineCommand.Null:
                        Console.Log("Null command recieved");
                        break;
                    case EngineCommand.Error:
                        Console.Log("Error occured");
                        break;

                    case EngineCommand.GetFps:
                    {
                        int fps = -1;

                        if(args.Length == 4)
                        {
                            fps = BitConverter.ToInt32(args);
                        }
                        else
                        {
                            Console.Log("Invalid args length of != 4 for reading an integer");
                        }

                        Console.Log($"Engine FPS Recieved as: '{fps}'");
                        PipeProcessing.UpdateFps(fps);
                        break;
                    }
                    case EngineCommand.SetFps:
                        Console.Log("Setting engine's FPS was successful");
                        break;                        
                }
            }
            private static void HandleRenderer(byte command, byte[] args)
            {
                
            }
            private static void HandleScene(byte command, byte[] args)
            {
                switch ((SceneCommand)command)
                {
                    case SceneCommand.Null:
                        Console.Log("Null command recieved");
                        break;
                    case SceneCommand.Error:
                        Console.Log("Error occured");
                        break;

                    case SceneCommand.ClearScene:
                    case SceneCommand.SaveScene:
                    case SceneCommand.LoadScene:
                        Console.Log($"'{(SceneCommand)command}' was a success");
                        break;           
                }
            }
        }

        namespace Enums {
            public enum Header : byte
            {
                Null = 0x00,

                Engine = 0x01,
                Renderer = 0x02,
                Scene   = 0x03,

                Error = 0xFF
            }

            public enum EngineCommand : byte
            {
                Null = 0x00,

                SetFps = 0x01,
                GetFps = 0x02,
                Play = 0x03,
                Pause = 0x04,
                
                Error = 0xFF
            }

            public enum RendererCommand : byte
            {
                Null = 0x00,

                // to be added later..
                Error = 0xFF
            }

            public enum SceneCommand : byte
            {
                Null = 0x00,

                LoadScene = 0x01,
                SaveScene = 0x02,
                ClearScene = 0x03,

                Error = 0xFF
            }
        }
    }
}