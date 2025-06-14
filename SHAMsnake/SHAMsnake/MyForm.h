#pragma once
#include <time.h>
#include <stdlib.h>

namespace SHAMsnake {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;
    using namespace System::Drawing::Text;

    /**
     * @class MyForm
     * @brief Главная форма приложения "Змейка".
     *
     * Класс реализует логику игры "Змейка", включая управление змейкой,
     * обработку столкновений, подсчет очков и отображение игрового поля.
     */
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        /**
         * @brief Конструктор класса MyForm.
         *
         * Инициализирует компоненты формы и настраивает двойную буферизацию
         * для устранения мерцания.
         */
        MyForm(void)
        {
            InitializeComponent();
            this->DoubleBuffered = true;
        }

    protected:
        /**
         * @brief Деструктор класса MyForm.
         *
         * Освобождает ресурсы, связанные с компонентами формы.
         */
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

        /**
         * @brief Метод отрисовки содержимого формы.
         * @param e Аргументы события отрисовки.
         *
         * Отрисовывает змейку, фрукт, а также текстовые сообщения
         * (например, "PAUSED" или "YOU WIN").
         */
        virtual void OnPaint(PaintEventArgs^ e) override sealed
        {
            __super::OnPaint(e);
            Graphics^ g = e->Graphics;

            // Отрисовка фрукта
            Brush^ fruitBrush = gcnew SolidBrush(Color::Red);
            g->FillEllipse(fruitBrush, fruitPosition.X, fruitPosition.Y, blockSize, blockSize);

            // Отрисовка змейки
            Brush^ snakeBrush = gcnew SolidBrush(Color::Green);
            for each(Point el in snake)
                g->FillRectangle(snakeBrush, el.X, el.Y, blockSize, blockSize);

            if (isPaused) {
                DrawCenteredText(g, "PAUSED", Color::White, 24);
            }
            else if (gameWon) {
                DrawCenteredText(g, "YOU WIN!", Color::Gold, 28);
                DrawCenteredTextWithOffset(g, "Press R to restart", Color::White, 16, 50);
            }
        }

    private:
        System::ComponentModel::Container^ components; ///< Контейнер для компонентов формы.
        List<Point>^ snake; ///< Список точек, представляющих сегменты змейки.
        Point fruitPosition; ///< Позиция фрукта на игровом поле.
        const int blockSize = 20; ///< Размер одного блока (сегмента змейки или фрукта).
        const int winScore = 10; ///< Количество очков, необходимых для победы.

        int fruitCount = 0; ///< Текущее количество собранных фруктов.
        int highScore = 0; ///< Рекордное количество очков.
        Label^ scoreLabel; ///< Метка для отображения текущего счета.
        Label^ highScoreLabel; ///< Метка для отображения рекорда.

        Timer^ timer; ///< Таймер для управления игровым циклом.
        int moveX = 1, moveY = 0; ///< Направление движения змейки.
        bool isPaused = false; ///< Флаг паузы.
        bool isSpeedBoost = false; ///< Флаг ускоренного режима.
        bool gameWon = false; ///< Флаг победы в игре.

        /**
         * @brief Отрисовывает текст по центру формы.
         * @param g Объект Graphics для отрисовки.
         * @param text Текст для отображения.
         * @param color Цвет текста.
         * @param fontSize Размер шрифта.
         */
        void DrawCenteredText(Graphics^ g, String^ text, Color color, int fontSize)
        {
            StringFormat^ format = gcnew StringFormat();
            format->Alignment = StringAlignment::Center;
            format->LineAlignment = StringAlignment::Center;

            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", fontSize, FontStyle::Bold);
            Brush^ brush = gcnew SolidBrush(color);

            RectangleF rect = RectangleF(0, 0, (float)this->ClientSize.Width, (float)this->ClientSize.Height);
            g->DrawString(text, font, brush, rect, format);
        }

        /**
         * @brief Отрисовывает текст по центру формы с вертикальным смещением.
         * @param g Объект Graphics для отрисовки.
         * @param text Текст для отображения.
         * @param color Цвет текста.
         * @param fontSize Размер шрифта.
         * @param yOffset Вертикальное смещение текста.
         */
        void DrawCenteredTextWithOffset(Graphics^ g, String^ text, Color color, int fontSize, int yOffset)
        {
            StringFormat^ format = gcnew StringFormat();
            format->Alignment = StringAlignment::Center;
            format->LineAlignment = StringAlignment::Center;

            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", fontSize, FontStyle::Bold);
            Brush^ brush = gcnew SolidBrush(color);

            RectangleF rect = RectangleF(0, (float)yOffset, (float)this->ClientSize.Width, (float)this->ClientSize.Height);
            g->DrawString(text, font, brush, rect, format);
        }

        /**
         * @brief Инициализирует компоненты формы.
         *
         * Настраивает размеры, заголовок, цвет фона, а также создает и размещает
         * элементы управления (метки для счета и рекорда). Также инициализирует
         * змейку, размещает фрукт и запускает игровой таймер.
         */
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Size = System::Drawing::Size(400, 400);
            this->Text = L"Snake Game";
            this->BackColor = Color::Black;
            this->Padding = System::Windows::Forms::Padding(0);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

            scoreLabel = gcnew Label();
            scoreLabel->ForeColor = Color::White;
            scoreLabel->BackColor = Color::Transparent;
            scoreLabel->Text = "Score: 0";
            scoreLabel->Location = Point(10, 10);
            this->Controls->Add(scoreLabel);

            highScoreLabel = gcnew Label();
            highScoreLabel->ForeColor = Color::White;
            highScoreLabel->BackColor = Color::Transparent;
            highScoreLabel->Text = "High Score: 0";
            highScoreLabel->Location = Point(10, 30);
            this->Controls->Add(highScoreLabel);

            snake = gcnew List<Point>();
            snake->Add(Point(100, 100));

            srand(static_cast<unsigned>(time(nullptr)));
            PlaceFruit();

            timer = gcnew Timer();
            timer->Interval = 100;
            timer->Tick += gcnew EventHandler(this, &MyForm::OnTimerTick);
            timer->Start();

            this->KeyDown += gcnew KeyEventHandler(this, &MyForm::OnKeyDown);
        }

        /**
         * @brief Размещает фрукт на игровом поле.
         *
         * Генерирует случайную позицию для фрукта, гарантируя, что он не
         * появится на сегментах змейки.
         */
        void PlaceFruit() {
            int maxX = this->ClientSize.Width / blockSize;
            int maxY = this->ClientSize.Height / blockSize;

            do {
                fruitPosition = Point(rand() % maxX * blockSize, rand() % maxY * blockSize);
            } while (snake->Contains(fruitPosition));
        }

        /**
         * @brief Обработчик события таймера.
         * @param sender Источник события.
         * @param e Аргументы события.
         *
         * Управляет игровым циклом: перемещает змейку, проверяет столкновения
         * и обновляет счет.
         */
        void OnTimerTick(Object^ sender, EventArgs^ e) {
            if (isPaused || gameWon) return;

            MoveSnake();

            if (snake[0].X < 0 || snake[0].Y < 0 ||
                snake[0].X >= this->ClientSize.Width ||
                snake[0].Y >= this->ClientSize.Height) {
                GameOver();
                return;
            }

            for (int i = 1; i < snake->Count; i++) {
                if (snake[0] == snake[i]) {
                    GameOver();
                    return;
                }
            }

            if (snake[0] == fruitPosition) {
                fruitCount++;
                scoreLabel->Text = "Score: " + fruitCount.ToString();

                if (fruitCount > highScore) {
                    highScore = fruitCount;
                    highScoreLabel->Text = "High Score: " + highScore.ToString();
                }

                if (fruitCount >= winScore) {
                    WinGame();
                    return;
                }

                GrowthSnake();
                PlaceFruit();
            }

            this->Invalidate();
        }

        /**
         * @brief Обрабатывает победу в игре.
         *
         * Останавливает таймер, устанавливает флаг победы и выводит сообщение.
         */
        void WinGame() {
            timer->Stop();
            gameWon = true;
            this->Invalidate();
            MessageBox::Show("Congratulations! You won with score: " + fruitCount.ToString());
        }

        /**
         * @brief Обрабатывает завершение игры.
         *
         * Останавливает таймер, выводит сообщение о завершении игры
         * и сбрасывает игровое состояние.
         */
        void GameOver() {
            timer->Stop();
            MessageBox::Show("Game over! Your score: " + fruitCount.ToString());
            ResetGame();
        }

        /**
         * @brief Сбрасывает игровое состояние.
         *
         * Возвращает змейку в начальное положение, сбрасывает счет
         * и запускает таймер.
         */
        void ResetGame() {
            snake->Clear();
            snake->Add(Point(100, 100));
            fruitCount = 0;
            scoreLabel->Text = "Score: 0";
            moveX = 1; moveY = 0;
            gameWon = false;
            PlaceFruit();
            timer->Start();
        }

        /**
         * @brief Перемещает змейку.
         *
         * Добавляет новый сегмент в направлении движения и удаляет последний сегмент.
         */
        void MoveSnake() {
            Point newHead = snake[0];

            newHead.X += moveX * blockSize;
            newHead.Y += moveY * blockSize;
            snake->Insert(0, newHead);
            snake->RemoveAt(snake->Count - 1);
        }

        /**
         * @brief Увеличивает длину змейки.
         *
         * Добавляет новый сегмент в направлении движения после съедания фрукта.
         */
        void GrowthSnake() {
            Point newHead = snake[0];

            newHead.X += moveX * blockSize;
            newHead.Y += moveY * blockSize;
            snake->Insert(0, newHead);
        }

        /**
         * @brief Обработчик события нажатия клавиши.
         * @param sender Источник события.
         * @param e Аргументы события.
         *
         * Управляет направлением движения змейки, паузой, ускорением
         * и перезапуском игры.
         */
        void OnKeyDown(Object^ sender, KeyEventArgs^ e) {
            if (gameWon && e->KeyCode != Keys::R) return;

            switch (e->KeyCode) {
            case Keys::Up:
                if (moveY != 1) {
                    moveX = 0;
                    moveY = -1;
                }
                break;
            case Keys::Down:
                if (moveY != -1) {
                    moveX = 0;
                    moveY = 1;
                }
                break;
            case Keys::Left:
                if (moveX != 1) {
                    moveX = -1;
                    moveY = 0;
                }
                break;
            case Keys::Right:
                if (moveX != -1) {
                    moveX = 1;
                    moveY = 0;
                }
                break;
            case Keys::Space:
                if (e->Shift) {
                    isSpeedBoost = !isSpeedBoost;
                    timer->Interval = isSpeedBoost ? 50 : 100;
                }
                else {
                    isPaused = !isPaused;
                    this->Invalidate();
                }
                break;
            case Keys::R:
                ResetGame();
                break;
            }
        }
    };
}