# Filter
Рестайлинг систему управления электрофильтра газоочистки.
Система управляет высоковольтными агрегатами питпния и механизмами регенерации.

	Класс Channel моделирует обмен информацией с контроьллерами полей фильтра.
В реальной системе данные от контроллера поступвют с интервалом 10 мс.
	Поток сhannel также, с итервалом 10 мс генерирует очередной байт информации, моделируя реальный 
канал связи с контроллером. При достижении конца пакета посылает сигнал в основний поток: emit send(last);

	Основной поток обрабатывае информацию канала, выводит на экран оперативные данные о напряжении
и токе електрофильтра, режиме работы (искровой, автоматический, стоп) и подает сигналы управления контроллерами.

	Класс Field описывает поле электрофильтра и имеет все органы управления и индикации состояния поля.
Количество полей фильтра, мощность установленных агрегатов питания - задается в файле config.xml
