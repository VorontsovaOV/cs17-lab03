#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>
using namespace std;

enum Scale
    {
      Kelvin,
      Celsiy,
      Farenheit
    };

struct Temperature
    {
        double value;
        Scale scale;
    };

istream& operator >> (istream& in, Temperature& t)
{
    in >> t.value;
    char symbol;
    in >> symbol;
    switch (symbol) {
    case 'K' :
        t.scale = Kelvin;
        break;
    case 'C' :
        t.scale = Celsiy;
        break;
    case 'F' :
        t.scale = Farenheit;
        break;
    }
    return in;
};

void test_temperature_input ()
{
 // создать поток в памяти с примерами
    istringstream in ("-15K");
    //считать значение в переменную
    Temperature result;
    in >> result;
    //проверить значение шкалы
    assert (result.value == -15);
    assert (result.scale == Kelvin);

    // создать поток в памяти с примерами
    istringstream in_2 ("23F");
    //считать значение в переменную
    in_2 >> result;
    //проверить значение шкалы
    assert (result.value == 23);
    assert (result.scale == Farenheit);

    // создать поток в памяти с примерами
    istringstream in_3 ("46C");
    //считать значение в переменную
    in_3 >> result;
    //проверить значение шкалы
    assert (result.value == 46);
    assert (result.scale == Celsiy);
}

Temperature convert (const Temperature& t, Scale scale)
    {double k;
        switch (t.scale) {
        case Kelvin :
            k = t.value;
            break;
        case Celsiy :
            k = t.value + 273;
            break;
        case Farenheit :
            k = (t.value - 32)/1.8;
            break;
        }
        Temperature result;
        result.scale = scale;
        switch (scale)
        {
        case Kelvin :
            result.value = k;
            break;
        case Celsiy :
            result.value = k + 273;
            break;
        case Farenheit :
            result.value = 1.8*k + 32;
            break;
        }
        return result;
    }

bool operator < (Temperature t1, Temperature t2) //истина t1<t2, ложь t1>=t2
{
    t1 = convert(t2,t1.scale);
    return t1.value < t2.value;
}

bool operator > (Temperature t1, Temperature t2) //истина t1>t2, ложь t1<=t2
{
    t1 = convert(t2,t1.scale);
    return t1.value > t2.value;
}

int
main() {


    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    vector<Temperature> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cin >> numbers[i];
    }

    size_t column_count;
    cerr << "Enter column count: ";
    cin >> column_count;

    Temperature min = numbers[0];
    Temperature max = numbers[0];
    for (Temperature number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }

    max = convert(max, min.scale);

    vector<size_t> counts(column_count);
    for (Temperature number : numbers) {
        number = convert(number, min.scale);
        size_t column = (size_t)((number.value - min.value) / (max.value - min.value) *
                column_count);
        if (column == column_count) {
            column--;
        }
        counts[column]++;
    }

    const size_t screen_width = 80;
    const size_t axis_width = 4;
    const size_t chart_width = screen_width - axis_width;

    // Можно было бы считать в предыдущем цикле, но так более наглядно.
    size_t max_count = 0;
    for (size_t count : counts) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > chart_width;

    for (size_t count : counts) {
        if (count < 100) {
            cout << ' ';
        }
        if (count < 10) {
            cout << ' ';
        }
        cout << count << "|";

        size_t height = count;
        if (scaling_needed) {
            // Point: код должен быть в первую очередь понятным.
            const double scaling_factor = (double)chart_width / max_count;
            height = (size_t)(count * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

    return 0;
}