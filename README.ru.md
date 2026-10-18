# ReyondBroom

**Самостоятельный 3D-редактор уровней для игр с брашевой геометрией.** Стройте пространство, создавайте архитектуру, настраивайте текстуры и размещайте игровые сущности — от первой комнаты до детальной игровой карты.

[![Скачать для Windows x64](https://img.shields.io/badge/Скачать_для_Windows_x64-0078D4?style=for-the-badge&logo=windows&logoColor=white)](https://github.com/reyond9079/ReyondBroom/releases/latest/download/ReyondBroom-Windows.zip)
[![Скачать для Linux x86_64](https://img.shields.io/badge/Скачать_для_Linux_x86__64-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://github.com/reyond9079/ReyondBroom/releases/latest/download/ReyondBroom-Linux-x86_64.AppImage)

[English](README.md) · **Русский** · [Руководство с иллюстрациями](https://reyond9079.github.io/ReyondBroom/index.ru.html) · [Полный справочник (EN)](https://reyond9079.github.io/ReyondBroom/reference.html) · [Релизы и контрольные суммы](https://github.com/reyond9079/ReyondBroom/releases/latest)

## Что добавляет ReyondBroom

По сравнению с базовым TrenchBroom 2026.2 в ReyondBroom доступны следующие дополнительные инструменты и возможности. Каждая ссылка ведёт к инструкции с иллюстрациями.

| Возможность | Что можно сделать |
| --- | --- |
| [Выпуклый Bevel](https://reyond9079.github.io/ReyondBroom/index.ru.html#bevel) | Скруглять рёбра, вершины или внешний контур выделенных граней. Настраивать радиус/отступ, сегменты и выпуклый профиль, ограничивать размер через Clamp внутри каждого браша и видеть результат прямо на сцене. |
| [Fracture](https://reyond9079.github.io/ReyondBroom/index.ru.html#fracture) | Разделять браш на 2–128 осколков Вороного с заданным Seed, назначать материал срезов, раздвигать осколки и при необходимости создавать отдельные `func_wall`. |
| [Perforate](https://reyond9079.github.io/ReyondBroom/index.ru.html#perforate) | Создавать случайные сквозные многоугольные отверстия с заданными количеством, числом сторон, диапазоном диаметров и расстоянием между ними; сохранять и выделять подходящие вставки `func_wall`. |
| [Settle](https://reyond9079.github.io/ReyondBroom/index.ru.html#settle) | Укладывать браши с физикой Bullet, трением, отскоком и начальным импульсом. Учитывать столкновения с брашами сцены и патчами Quake 3, затем сохранять результат как статическую геометрию карты. |
| [Terrain](https://reyond9079.github.io/ReyondBroom/index.ru.html#terrain), [Sculpt](https://reyond9079.github.io/ReyondBroom/index.ru.html#sculpt) и [Rock](https://reyond9079.github.io/ReyondBroom/index.ru.html#rock) | Генерировать рельеф и камни, редактировать рельеф инструментом скульптинга. |
| [Polygon Cut / Spawn](https://reyond9079.github.io/ReyondBroom/index.ru.html#polygon-cut) | Рисовать многоугольные контуры для вырезов в существующей геометрии или создания новых объёмов. |
| [Inset](https://reyond9079.github.io/ReyondBroom/index.ru.html#inset), [Spin](https://reyond9079.github.io/ReyondBroom/index.ru.html#spin) и [Bezier Bend](https://reyond9079.github.io/ReyondBroom/index.ru.html#bezier-bend) | Создавать внутренние отступы поверхностей, цепочки экструзий с поворотом и изгибать группы вдоль кривой. |
| [Subdivision](https://reyond9079.github.io/ReyondBroom/index.ru.html#subdivision), [Subtract 2](https://reyond9079.github.io/ReyondBroom/index.ru.html#subtract-2) и [Convert Triang Brushes](https://reyond9079.github.io/ReyondBroom/index.ru.html#convert-triang) | Добавлять разбиения геометрии, применять альтернативное вычитание и преобразовывать триангулированные брашевые структуры. |
| [Массивы](https://reyond9079.github.io/ReyondBroom/index.ru.html#array-line) и [Symmetry](https://reyond9079.github.io/ReyondBroom/index.ru.html#symmetry) | Создавать линейные, круговые и случайные размещения, поддерживать симметричные копии. |
| [Grid Rotation](https://reyond9079.github.io/ReyondBroom/index.ru.html#grid-rotation), [Auto Integer Snap](https://reyond9079.github.io/ReyondBroom/index.ru.html#snap-integer) и [XYZ](https://reyond9079.github.io/ReyondBroom/index.ru.html#xyz) | Работать с повёрнутой сеткой, привязывать геометрию к целым координатам и задавать точные позиции. |
| [Коллекции префабов](https://reyond9079.github.io/ReyondBroom/index.ru.html#prefabs) и [EntityList](https://reyond9079.github.io/ReyondBroom/index.ru.html#entity-list) | Повторно использовать сохранённые конструкции и находить размещённые сущности в отдельном списке. |
| [Управление браузерами материалов и сущностей](https://reyond9079.github.io/ReyondBroom/index.ru.html#material-browser) | Настраивать размер предпросмотра, подключать папки текстур и выбирать палитру экспорта WAD. |
| [Предпросмотры Quake](https://reyond9079.github.io/ReyondBroom/index.ru.html#lighting) и [Spawn Master](https://reyond9079.github.io/ReyondBroom/index.ru.html#spawn-master) | Просматривать свет, небо, двери, кнопки, лифты, поезда и камеры intermission; создавать схемы появления сущностей через телепортационные комнаты. |
| [Unity Sync](https://reyond9079.github.io/ReyondBroom/index.ru.html#unity-sync) | Экспортировать геометрию и текстуры карты в префаб Unity с настраиваемым масштабом. |

Bevel создаёт только выпуклые браши. Флаг **No collide** в Fracture создаёт сущности `func_wall`, но **не отключает** столкновения в Settle. Игровые предпросмотры приблизительны и не заменяют проверку скомпилированной карты.

![ReyondBroom: предпросмотр выпуклого Bevel в окне карты](docs/captures/reyond/bevel-preview.png)

## Всё для построения уровня

- **Редактирование в 3D и 2D.** Примитивы, вершины, рёбра, грани, отсечение, экструзия, Sweep, масштаб и скос. Патчи Quake 3 с управляющими точками в поддерживаемых форматах.
- **Архитектура и ландшафт.** Вырезы и объёмы по контуру, рамки Inset, изгиб групп, цепочки экструзий, разбиение поверхностей, скульптинг, генерация рельефа и камней.
- **Скругление и разрушение.** Bevel по внешнему контуру граней, рёбрам или вершинам с радиусом, сегментами, выпуклым профилем и Clamp. Раскол Fracture, сквозные отверстия Perforate и укладка Settle с гравитацией и столкновениями.
- **Повторение и точность.** Линейные, круговые и случайные массивы, симметрия, поворот сетки, целочисленная привязка и точные XYZ-координаты.
- **Текстуры и организация.** UV-редактор, коллекции материалов, папки текстур, палитры экспорта WAD, префабы и поиск EntityList. Группы, связанные группы и слои помогают работать с большими картами.
- **Предпросмотр и экспорт.** Приблизительный свет и небо Quake, движение сущностей и маршруты поездов. Внешние компиляторы, диагностика, поиск утечек, запуск игры и синхронизация геометрии с текстурами в Unity.

ReyondBroom развивается независимо, имеет собственные релизы и документацию. Он устанавливается как полноценная программа; другой редактор для работы не нужен.

## Начало работы

1. **Установите редактор.** В Windows распакуйте весь ZIP и запустите `TrenchBroom.exe` — это текущее имя исполняемого файла. Сохраните рядом ресурсы и DLL. В Linux разрешите запуск AppImage; при отсутствии FUSE добавьте `--appimage-extract-and-run`.
2. **Выберите игру.** Создайте карту в совместимом формате, укажите каталог игры, мод и определения сущностей. Игровые ресурсы и компиляторы устанавливаются отдельно.
3. **Постройте комнату.** Создайте пол, стены и потолок, добавьте точку старта и свет, назначьте материалы и сохраните карту.
4. **Соберите и проверьте.** Настройте **Run → Compile** под инструменты вашей игры. До детализации проверьте результат в движке.

[Пошаговая первая карта с иллюстрациями →](https://reyond9079.github.io/ReyondBroom/index.ru.html#first-room)

Готовые сборки доступны для Windows x64 и Linux x86_64. AppImage проверяется на Ubuntu 24.04; старые дистрибутивы не проверены. macOS-билда в текущем релизе нет.

## Руководство по инструментам

| Задача | Инструкция |
| --- | --- |
| Навигация, выделение, построение и текстуры | [Начало работы](https://reyond9079.github.io/ReyondBroom/index.ru.html#start) |
| Скруглить рёбра и углы | [Bevel](https://reyond9079.github.io/ReyondBroom/index.ru.html#bevel) |
| Разбить стену и уложить обломки | [Fracture](https://reyond9079.github.io/ReyondBroom/index.ru.html#fracture) · [Settle](https://reyond9079.github.io/ReyondBroom/index.ru.html#settle) |
| Создать случайные сквозные отверстия | [Perforate](https://reyond9079.github.io/ReyondBroom/index.ru.html#perforate) |
| Создать ландшафт и криволинейные конструкции | [Terrain](https://reyond9079.github.io/ReyondBroom/index.ru.html#terrain) · [Bezier Bend](https://reyond9079.github.io/ReyondBroom/index.ru.html#bezier-bend) · [Spin](https://reyond9079.github.io/ReyondBroom/index.ru.html#spin) |
| Повторять модули и размещать заготовки | [Array](https://reyond9079.github.io/ReyondBroom/index.ru.html#array-line) · [Symmetry](https://reyond9079.github.io/ReyondBroom/index.ru.html#symmetry) · [Prefabs](https://reyond9079.github.io/ReyondBroom/index.ru.html#prefabs) |
| Собрать, проверить и экспортировать | [Компиляция](https://reyond9079.github.io/ReyondBroom/index.ru.html#compile) · [Unity Sync](https://reyond9079.github.io/ReyondBroom/index.ru.html#unity-sync) |

Руководство содержит одинаковый набор глав на английском и русском: шаги, параметры, ограничения, скриншоты и поиск. Полный технический справочник по базовому редактору, выражениям и конфигурациям игр доступен на английском. [Исходники документации и инструкция локальной сборки](docs/README.md) находятся в репозитории.

## Игры и форматы

Предусмотрены конфигурации Quake, Quake 2, Quake 3, Hexen 2, Daikatana и собственных движков. Форматы карт, материалы, классы сущностей и патчи зависят от конфигурации. Поддерживаются Quake Standard и Valve 220. Выбирайте формат, который понимает ваш компилятор; предпросмотр не заменяет проверку готовой карты в игре.

## Разработка и справочная информация

Рабочая ветка — **ReyondBroom**. Инструкции сборки и правила репозитория находятся в [BUILD.md](BUILD.md), [CONTRIBUTING.md](CONTRIBUTING.md) и [AGENTS.md](AGENTS.md).

Происхождение проекта и иллюстраций собрано в одном разделе [«Источники и лицензии»](https://reyond9079.github.io/ReyondBroom/sources.html). Лицензия — [GPL-3.0-or-later](LICENSE.txt); исходные уведомления и [лицензии сторонних компонентов](THIRD_PARTY_NOTICES.ru.md) сохранены.
