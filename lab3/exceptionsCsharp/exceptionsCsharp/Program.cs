using System;
using System.Collections.Generic;

class Program
{
    // Целочисленная арифметика
    static void IntegerArithmetic()
    {
        try
        {
            short result = 32767;
            if (result == short.MaxValue)
                throw new Exception("сложение с максимальным числом.");
            result += 1;
        }
        catch (Exception e)
        {
            Console.WriteLine($"Переполнение целого числа: {e.Message}");
        }

        try
        {
            int denominator = 0;
            //if (denominator == 0)
            //    throw new Exception("Деление на ноль.");
            int result = 42 / denominator;
        }
        catch (Exception e)
        {
            Console.WriteLine($"Деление целого числа на ноль: {e.Message}");
        }
    }

    // Работа с плавающей точкой
    static void DoubleArithmetic()
    {
        try
        {
            int a = -1;
            if (a < 0)
                throw new Exception("Вычисление корня из отрицательного числа");
            double result = Math.Sqrt(-1);
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при вычислении корня: {e.Message}");
        }

        try
        {
            double denominator = 0.0;
            if (denominator == 0.0)
                throw new Exception("Деление на ноль.");
            double result = 42.0 / denominator;
        }
        catch (Exception e)
        {
            Console.WriteLine($"Деление вещественного числа на ноль: {e.Message}");
        }
    }

    // Работа с динамикой
    static void WorkWithDynamic()
    {
        try
        {
            int[] array = null;
            //if (array == null)
            //    throw new Exception("Пустая ссылка.");
            int value = array[0];
        }
        catch (Exception e)
        {
            Console.WriteLine($"Ошибка при обращении к пустому массиву: {e.Message}");
        }

        try
        {
            List<int> list = new List<int>();
            int value2 = list[15];
        }
        catch (ArgumentOutOfRangeException e)
        {
            Console.WriteLine($"Обращение за пределы списка: {e.Message}");
        }

        //var list = new System.Collections.Generic.List<int>();
        //try
        //{
        //    while (true)
        //    {
        //        list.Add(1);
        //    }
        //}
        //catch (OutOfMemoryException ex)
        //{
        //    Console.WriteLine($"Memory ran out after inserting {list.Count} elements");
        //}
    }

    static void Main()
    {
        // Установка культуры
        System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("ru-RU");

        IntegerArithmetic();
        DoubleArithmetic();
        WorkWithDynamic();
    }
}
