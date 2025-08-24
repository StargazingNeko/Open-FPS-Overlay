using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Web.Script.Serialization;
using System.Windows;
using System.Windows.Input;
using System.Windows.Interop;

namespace Open_FPS_Overlay
{

    public partial class MainWindow : Window
    { 
        JavaScriptSerializer jss = new JavaScriptSerializer();
        KeyConverter convertKey = new KeyConverter();

        private HwndSource _source;
        private const int HOTKEY_ID = 9000;

        public MainWindow()
        {
            InitializeComponent();
            if (!File.Exists("config.json"))
            {
                var defaultConfig = new Dictionary<string, dynamic>
                {
                    { "Hotkey", Key.F11 }
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

        #region Register Hotkey
        private void RegisterHotKey() {
            var helper = new WindowInteropHelper(this);
            const uint VK_F10 = 0x79;
            const uint MOD_CTRL = 0x0002;
            if (!RegisterHotKey(helper.Handle, HOTKEY_ID, MOD_CTRL, VK_F10)) { // Handles error for Control + F10
                // handle error
            }
        }
        #endregion

        #region Remove/unbind Hotkey
        private void UnregisterHotKey() {
            var helper = new WindowInteropHelper(this);
            UnregisterHotKey(helper.Handle, HOTKEY_ID);
        }
        #endregion

        #region Private Methods
        private IntPtr HwndHook(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled) {
            const int WM_HOTKEY = 0x0312;
            switch (msg) {
                case WM_HOTKEY:
                    switch (wParam.ToInt32()) {
                        case HOTKEY_ID:
                            OnHotKeyPressed();
                            handled = true;
                            break;
                    }
                    break;
            }
            return IntPtr.Zero;
        }

        private void OnHotKeyPressed() {
            Console.WriteLine("Binding pressed");
        }
        #endregion

        #region Dll Imports
        [DllImport("User32.dll")]
        private static extern bool RegisterHotKey(
            [In] IntPtr hWnd,
            [In] int id,
            [In] uint fsModifiers,
            [In] uint vk);

        [DllImport("User32.dll")]
        private static extern bool UnregisterHotKey(
            [In] IntPtr hWnd,
            [In] int id);

        #endregion

        #region Protected Overrides
        protected override void OnSourceInitialized(EventArgs e) {
            base.OnSourceInitialized(e);
            var helper = new WindowInteropHelper(this);
            _source = HwndSource.FromHwnd(helper.Handle);
            _source.AddHook(HwndHook);
            RegisterHotKey();
        }

        protected override void OnClosed(EventArgs e) {
            _source.RemoveHook(HwndHook);
            _source = null;
            UnregisterHotKey();
            base.OnClosed(e);
        }

        #endregion
    }
}
