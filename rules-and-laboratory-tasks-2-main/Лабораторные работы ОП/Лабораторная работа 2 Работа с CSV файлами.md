# Лабораторная работа №2 "Работа с CSV файлами"

## Архитектура приложения

Программа должна состоять из двух доменов: "бизнес-логики" и "интерфейса". Связь между доменами реализуется при помощи модуля единой точки входа.

#### Модуль "бизнес-логики"
Реализует все операции над файлами и данными. Модуль должен быть написан в структурном стиле. В модуле можно использовать только стандартные возможности языка C. Использование функций Qt в модуле "бизнес-логики" запрещено. Выделение и освобождение памяти осуществляется при помощи функций `malloc, calloc, realloc, free`.

#### Модуль интерфейса
Реализует логику отображения интерфейса приложения. Использует классы Qt. Никаких вычислений в нем производиться не может, он отвечает исключительно за визуализацию и передачу управляющих команд.

#### Единая точка входа
Реализует логику передачи команд от интерфейса к модулю "бизнес-логики" и возврат результата вычисления в интерфейс. Состоит из модуля принятия решения и структуры контекста, которая может хранить информацию о текущей операции, считанных данных, информацию об ошибке и иную информацию, необходимую для передачи между слоями.

## Задание
разработать на Qt программу для визуализации табличных данных и вычисления по ним статистических метрик.

Разработанная программа должна обладать графическим интерфейсом, содержащим: 

1.	кнопку для выбора открываемого файла (fileDialog) и поле для вывода его 
названия;
2.	таблицу, при помощи которой будут визуализироваться данные;
3.	поле для ввода названия региона;
4.	поле для ввода номера колонки;
5.	кнопку "Load data";
6.	кнопку "Calculate metrics";
7.	поля для вывода статистических метрик.

По нажатию на кнопку "Load data" данные из файла должны быть загружены. В таблице должны отобразиться строки для региона, указанного в соответствующем поле, либо все данные, если регион не выбран.

В результате считывания файла должно быть отображено информационное окно с общим количеством строк в файле, количеством строк содержащих ошибку и количеством успешно считанных строк. В таблице должны быть отображены только те структуры, строки которых, не содержат пустых полей или ошибок в полях.

Строка `csv` файла должна быть преобразована в структуру сразу после считывания. Структуры необходимо сохранить в динамическую структуру данных. 

Преобразование структуры в строку таблицы должно происходить в модуле интерфейса.


В случае ошибки в файле программа должна уведомить об этом пользователя, прекратить загрузку файла и продолжить работу (без аварийного завершения программы). 

По нажатию на кнопку "Calculate metrics" программа должна произвести расчет статистических метрик (минимум, максимум, медиана) для региона, указанного в поле для ввода названия региона и колонки с номером из поля для ввода номера колонки.

Если хотя бы в одном из этих полей введены некорректные значения – программа должна уведомить об этом пользователя и прекратить расчет (без аварийного завершения программы). 

Рассчитанные значения должны быть выведены в соответствующих полях интерфейса. 

*Входные данные:*

* csv-файл с данными (russian demographic.csv);
* название региона;
* номер колонки, по которой будут вычислены статистические метрики. 

*Выходные данные (результат):*

* таблица, со всеми данными или по конкретному региону, визуализированная в программе;
* вычисленные максимум, минимум и медиана по данным из выбранной колонки, выведенные в текстовых полях.

### Пример входных данных
В примере строки, для удобства, пронумерованы, в реальном файле нумерации нет. 

Содержимое CSV файла:

```
1) year,region,natural_population_growth,birth_rate,death_rate,general_demographic_w 
eight,urbanization 
2) 1990,Republic of Adygea,1.9,14.2,12.3,84.66,52.42 
3) 1990,Altai Krai,1.8,12.9,11.1,80.24,58.07 
4) 1990,Amur Oblast,7.6,16.2,8.6,69.55,68.37 
... 
87) 1991,Republic of Adygea,0,13.5,13.5,85.42,52.51 
88) 1991,Altai Krai,0.4,11.7,11.3,79.95,58.08 
89) 1991,Amur Oblast,5.3,14.3,9,70.26,68.53 
... 
2297) 2017,Republic of Adygea,-2,10.6,12.6,80.22,47.3 
2298) 2017,Altai Krai,-3.2,10.8,14,83.61,56.3 
2299) 2017,Amur Oblast,-1.6,11.8,13.4,75.14,67.3
```

**Примечание**
```
year - год
region - область
natural_population_growth - естественный прирост населения
birth_rate - рождаемость
death_rate - смертность
general_demographic_weight - доля коренного населения
urbanization - доля городского населения
```

*Вводимые данные:*

| <!-- -->          | <!-- -->           |
|:------------------|--------------------|
| Название региона: | Republic of Adygea |
| Номер колонки:    | 3 (начинаются с 1) |

*Пример выходных данных:*

Для файла russian_demography.csv и входных данных из примера.

| <!-- -->  | <!-- -->|
|:----------|-----:|
| Минимум:  | -5.9 |
| Максимум: | 1.9  |
| Медиана:  | -3.2 |
