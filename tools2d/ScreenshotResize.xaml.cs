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
            if (openFileDialog.ShowDialog() == true)
            {
                Bitmap bitmap = new Bitmap(openFileDialog.FileName);

                System.Drawing.Size size;
                string filename;

                if (bitmap.Width < bitmap.Height)
                    size = new System.Drawing.Size(1242, 2208);
                else
                    size = new System.Drawing.Size(2208, 1242);
                filename = openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - 4) + string.Format("-{0}x{1}.jpg",size.Width,size.Height);
                ResizeImage(bitmap, size, filename);

                if (bitmap.Width < bitmap.Height)
                    size = new System.Drawing.Size(640, 1136);
                else
                    size = new System.Drawing.Size(1136, 640);
                filename = openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - 4) + string.Format("-{0}x{1}.jpg", size.Width, size.Height);
                ResizeImage(bitmap, size, filename);

                if (bitmap.Width < bitmap.Height)
                    size = new System.Drawing.Size(750, 1334);
                else
                    size = new System.Drawing.Size(1334, 750);
                filename = openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - 4) + string.Format("-{0}x{1}.jpg", size.Width, size.Height);
                ResizeImage(bitmap, size, filename);
            }
        }
        private void ResizeImage(Bitmap bitmap, System.Drawing.Size size,string filename) {
            Bitmap newBitmap = new Bitmap(bitmap, size);
            newBitmap.Save(filename, ImageFormat.Jpeg);
        }
    }
}
