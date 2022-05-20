using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace arduino_test
{
    public partial class Form1 : Form
    {
        System.IO.Ports.SerialPort Arduino;
        public Form1()
        {
            InitializeComponent();
            Arduino = new System.IO.Ports.SerialPort(); //renombra al puerto serial como arduino
            comboBox1.SelectedIndex = 2; //selecciona "COM3" del listado comboBox1, como item por defecto

            textBox1.Text = "Desconectado";
            textBox1.BackColor = Color.Red; //indica que el puerto COM esta desconectado por defecto
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                Arduino.WriteLine(richTextBox2.Text.ToString()); //envia lo que contiene richTextBox2 al arduino
                //timer1.Enabled = true; //inicia el timer, el que monitorea la salida de arduino
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }           
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        { 
            if (Arduino.IsOpen)
            {
                Arduino.Close(); //al cerrar el Form, el puerto COM tambien es cerrado
            }
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                timer1.Enabled = true; //inicia el timer, el que monitorea la salida de arduino
                Arduino.PortName = comboBox1.SelectedItem.ToString(); //el puerto de conexion es el seleccionado en el comboBox1
                Arduino.BaudRate = 9600;

                if (!Arduino.IsOpen)
                {
                    Arduino.Open(); //conecta el puerto COM
                    textBox1.Text = "Conectado";
                    textBox1.BackColor = Color.Lime; //cuando el puerto COM se conecta, un label coloreado lo indica
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        private void button3_Click(object sender, EventArgs e)
        { 
            timer1.Enabled = false;
            if (Arduino.IsOpen)
            {
                Arduino.Close(); //desconecta el puerto COM
                textBox1.Text = "Desconectado";
                textBox1.BackColor = Color.Red; //cuando el puerto COM se desconecta, un label coloreado lo indica
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                if (Arduino.IsOpen)
                {
                    string salida = Arduino.ReadExisting().ToString(); //guarda en string "salida" la salida entregada por el arduino
                    if (salida.Length > 0)
                    {
                        richTextBox1.Text = salida; //guarda en richTextBox1 la ultima salida del arduino
                        //richTextBox1.Text += salida + "\n"; //concatena todas las salidas del arduino y las guarda en richTextBox1
                    }
                }
            } catch (Exception ex) 
            {
                MessageBox.Show(ex.Message);
            }
            
        }

        private void button6_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            if (Arduino.IsOpen)
            {
                Arduino.Close(); //desconecta el puerto COM
                textBox1.Text = "Desconectado";
                textBox1.BackColor = Color.Red; //cuando el puerto COM se desconecta, un label coloreado lo indica
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
           // timer1.Enabled = true; //inicia el timer, el que monitorea la salida de arduino
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                File.WriteAllLines(saveFileDialog1.FileName + " .txt", richTextBox1.Lines);
        }
    }
}
