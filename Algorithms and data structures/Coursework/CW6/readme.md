### Цель работы

Разработать последовательную структуру данных для представления простейшей базы данных на файлах СП Си в соответствии с заданным вариантом. Составить программу генерации внешнего нетекстового файла заданной структуры, содержащего представительный набор записей (15-20). Распечатать содержимое сгенерированного файла в виде таблицы и выполнить над ним заданное действие для 2-3 значений параметров запроса p и распечатать результат.

Действие по выборке данных из файла оформить в виде отдельной программы с параметрами запроса, вводимыми из стандартного входного текстового файла, или получаемых из командной строки Unix. Второй способ задания параметров обязателен для работ, оцениваемых на хорошо и отлично. Параметры задаются с помощью ключей -f (распечатка файла) или -p (параметры конкретного варианта задания). Получение параметров из командной строки производится с помощью стандартных библиотечных функций argc и argv.
Структуры данных и константы, совместно используемые программами, следует вынести в отдельный заголовочный файл.

В процессе отладки и тестирования рекомендуется использовать команды обработки текстовых файлов ОС Unix и переадресацию ввода-вывода. Сгенерированные и отформатированные тестовые данные необходимо заранее поместить в текстовые файлы и распечатывать при протоколировании. Рекомендуется подобрать реальные и правдоподобные тестовые данные. Число наборов тестовых данных должно быть не менее трех. Имя файла с бинарными данными является обязательным параметром второй программы.
Отчет должен содержать оценку пространственной и временной сложности использованного алгоритма. В состав отчета также рекомендуется включить графическую иллюстрацию структуры файла и запроса на выборку.

### Задание:

Общая информация о выпускниках школы студента: фамилия, инициалы, пол, номер класса, буква класса, в каком ВУЗ-е учится, где работает, в каком полку служит и т. п.
Выяснить, имеются ли однофамильцы в каких-либо параллельных классах.