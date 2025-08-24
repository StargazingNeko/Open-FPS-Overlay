using System;
using System.Collections.Generic;
using System.IO;
using System.Web.Script.Serialization;
using System.Windows;
using System.Windows.Input;

namespace Open_FPS_Overlay
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    { 
        JavaScriptSerializer jss = new JavaScriptSerializer();
        KeyConverter convertKey = new KeyConverter();
        
        public MainWindow()
        {
            InitializeComponent();
            if (!File.Exists("config.json"))
            {
                var defaultConfig = new Dictionary<string, dynamic>
                {
                    { "Hotkey", Key.F12 }
                };
                File.WriteAllText("config.json", jss.Serialize(defaultConfig));
            }
            var dict = jss.Deserialize<Dictionary<string, dynamic>>(File.ReadAllText("config.json"));
            Key Hotkey_Id = (Key)dict["Hotkey"];
            Bound_Text.Text = convertKey.ConvertToString(Hotkey_Id);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("New Keybinding Requested");
            Bound_Text.Text = "...";
            
        }
    }
}
