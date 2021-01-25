using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread t = new Thread(new ThreadStart(() => { for (int i = 0; i < 10; i++) { Console.WriteLine(i); } }));
            Task task = new Task(new Action(() => { for (int i = 0; i < 10; i++) { Console.WriteLine(i); } }));
            print10();
        }        

        async static void print10() {
            await Task.Run(() => { for (int i = 0; i < 10; i++) { Console.WriteLine(i); } });
            for (int i = 0; i < 10; i++) { Console.WriteLine(i); }
        }
    }

}
