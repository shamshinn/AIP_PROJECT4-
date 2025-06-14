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
     * @brief ������� ����� ���������� "������".
     *
     * ����� ��������� ������ ���� "������", ������� ���������� �������,
     * ��������� ������������, ������� ����� � ����������� �������� ����.
     */
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        /**
         * @brief ����������� ������ MyForm.
         *
         * �������������� ���������� ����� � ����������� ������� �����������
         * ��� ���������� ��������.
         */
        MyForm(void)
        {
            InitializeComponent();
            this->DoubleBuffered = true;
        }

    protected:
        /**
         * @brief ���������� ������ MyForm.
         *
         * ����������� �������, ��������� � ������������ �����.
         */
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

        /**
         * @brief ����� ��������� ����������� �����.
         * @param e ��������� ������� ���������.
         *
         * ������������ ������, �����, � ����� ��������� ���������
         * (��������, "PAUSED" ��� "YOU WIN").
         */
        virtual void OnPaint(PaintEventArgs^ e) override sealed
        {
            __super::OnPaint(e);
            Graphics^ g = e->Graphics;

            // ��������� ������
            Brush^ fruitBrush = gcnew SolidBrush(Color::Red);
            g->FillEllipse(fruitBrush, fruitPosition.X, fruitPosition.Y, blockSize, blockSize);

            // ��������� ������
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
        System::ComponentModel::Container^ components; ///< ��������� ��� ����������� �����.
        List<Point>^ snake; ///< ������ �����, �������������� �������� ������.
        Point fruitPosition; ///< ������� ������ �� ������� ����.
        const int blockSize = 20; ///< ������ ������ ����� (�������� ������ ��� ������).
        const int winScore = 10; ///< ���������� �����, ����������� ��� ������.

        int fruitCount = 0; ///< ������� ���������� ��������� �������.
        int highScore = 0; ///< ��������� ���������� �����.
        Label^ scoreLabel; ///< ����� ��� ����������� �������� �����.
        Label^ highScoreLabel; ///< ����� ��� ����������� �������.

        Timer^ timer; ///< ������ ��� ���������� ������� ������.
        int moveX = 1, moveY = 0; ///< ����������� �������� ������.
        bool isPaused = false; ///< ���� �����.
        bool isSpeedBoost = false; ///< ���� ����������� ������.
        bool gameWon = false; ///< ���� ������ � ����.

        /**
         * @brief ������������ ����� �� ������ �����.
         * @param g ������ Graphics ��� ���������.
         * @param text ����� ��� �����������.
         * @param color ���� ������.
         * @param fontSize ������ ������.
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
         * @brief ������������ ����� �� ������ ����� � ������������ ���������.
         * @param g ������ Graphics ��� ���������.
         * @param text ����� ��� �����������.
         * @param color ���� ������.
         * @param fontSize ������ ������.
         * @param yOffset ������������ �������� ������.
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
         * @brief �������������� ���������� �����.
         *
         * ����������� �������, ���������, ���� ����, � ����� ������� � ���������
         * �������� ���������� (����� ��� ����� � �������). ����� ��������������
         * ������, ��������� ����� � ��������� ������� ������.
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
         * @brief ��������� ����� �� ������� ����.
         *
         * ���������� ��������� ������� ��� ������, ����������, ��� �� ��
         * �������� �� ��������� ������.
         */
        void PlaceFruit() {
            int maxX = this->ClientSize.Width / blockSize;
            int maxY = this->ClientSize.Height / blockSize;

            do {
                fruitPosition = Point(rand() % maxX * blockSize, rand() % maxY * blockSize);
            } while (snake->Contains(fruitPosition));
        }

        /**
         * @brief ���������� ������� �������.
         * @param sender �������� �������.
         * @param e ��������� �������.
         *
         * ��������� ������� ������: ���������� ������, ��������� ������������
         * � ��������� ����.
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
         * @brief ������������ ������ � ����.
         *
         * ������������� ������, ������������� ���� ������ � ������� ���������.
         */
        void WinGame() {
            timer->Stop();
            gameWon = true;
            this->Invalidate();
            MessageBox::Show("Congratulations! You won with score: " + fruitCount.ToString());
        }

        /**
         * @brief ������������ ���������� ����.
         *
         * ������������� ������, ������� ��������� � ���������� ����
         * � ���������� ������� ���������.
         */
        void GameOver() {
            timer->Stop();
            MessageBox::Show("Game over! Your score: " + fruitCount.ToString());
            ResetGame();
        }

        /**
         * @brief ���������� ������� ���������.
         *
         * ���������� ������ � ��������� ���������, ���������� ����
         * � ��������� ������.
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
         * @brief ���������� ������.
         *
         * ��������� ����� ������� � ����������� �������� � ������� ��������� �������.
         */
        void MoveSnake() {
            Point newHead = snake[0];

            newHead.X += moveX * blockSize;
            newHead.Y += moveY * blockSize;
            snake->Insert(0, newHead);
            snake->RemoveAt(snake->Count - 1);
        }

        /**
         * @brief ����������� ����� ������.
         *
         * ��������� ����� ������� � ����������� �������� ����� �������� ������.
         */
        void GrowthSnake() {
            Point newHead = snake[0];

            newHead.X += moveX * blockSize;
            newHead.Y += moveY * blockSize;
            snake->Insert(0, newHead);
        }

        /**
         * @brief ���������� ������� ������� �������.
         * @param sender �������� �������.
         * @param e ��������� �������.
         *
         * ��������� ������������ �������� ������, ������, ����������
         * � ������������ ����.
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