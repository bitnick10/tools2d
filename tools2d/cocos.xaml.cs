using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace tools2d
{
    /// <summary>
    /// Interaction logic for cocos.xaml
    /// </summary>
    public partial class cocos : Window
    {
        public cocos()
        {
            InitializeComponent();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string cmdText = @"D:\cocos2d-x-3.5\tools\cocos2d-console\bin\cocos";
            string args = "new " + projectName.Text + " -p " + "com.yourcompany." + projectName.Text + " -l cpp -d " + location.Text.Replace(@"\", "/");
            Process proc = Process.Start(cmdText, args);
        }
    }
}
