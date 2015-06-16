using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
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
    /// Interaction logic for ScreenshotResize.xaml
    /// </summary>
    public partial class ScreenshotResize : Window
    {
        public ScreenshotResize()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (openFileDialog.ShowDialog() == true) {
                Bitmap bitmap = new Bitmap(openFileDialog.FileName);

                System.Drawing.Size size = new System.Drawing.Size(1242,2208);
                Bitmap bitmap_1242x2208 = new Bitmap(bitmap, size);
                bitmap_1242x2208.Save(openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - 4) + "-1242x2208.jpg", ImageFormat.Jpeg);

                System.Drawing.Size size2 = new System.Drawing.Size(640, 1136);
                Bitmap bitmap_640x1136 = new Bitmap(bitmap, size2);
                bitmap_640x1136.Save(openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - 4) + "-640x1136.jpg",ImageFormat.Jpeg);

                System.Drawing.Size size3 = new System.Drawing.Size(750, 1334);
                Bitmap bitmap_750x1334 = new Bitmap(bitmap, size3);
                bitmap_750x1334.Save(openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - 4) + "-750x1334.jpg",ImageFormat.Jpeg);
            }
        }
    }
}
