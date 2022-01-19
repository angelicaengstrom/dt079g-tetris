//
// Created by angel on 2022-01-10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Window.h" resolved
/*!
 * @file window.cpp
 *
 * @brief window.cpp implementerar klassen Window
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */

#include "window.h"
#include "ui_window.h"
#include <QGridLayout>

/*!
 * Definerar en layout för fönstret
 */
Window::Window(QWidget *parent) :
        QWidget(parent), ui(new Ui::Window), board(new Board) {
    ui->setupUi(this);

    std::unique_ptr<QGridLayout> layout = std::make_unique<QGridLayout>();

    //Sätter bakrundsfärgen på fönstret
    std::unique_ptr<QPalette> palette = std::make_unique<QPalette>();
    palette->setColor(backgroundRole(), Qt::black);
    palette->setColor(foregroundRole(), Qt::black);
    setPalette(*palette);

    setStyleSheet("QWidget { background-color :  #373737;}"
                  "QPushButton { background-color : #5296A5; color : #373737; font-family: Tahoma; "
                  "font-size: 16px; border: 0px; padding: 12px 28px; letter-spacing: 3px;} "
                   "QPushButton:hover { background-color : #3D707B; color : #373737; }"
                   "QLabel { background-color : #373737; color : #3D707B; font-family: Tahoma; font-size: 16px; letter-spacing: 2px;"
                   " margin-left:auto; margin-right:auto; }");

    //Skapar visuellt område för poänginteger
    scoreLabel = new QLabel();
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("font-size: 20px; color : #5296A5; background-color: #292929");

    //Skapar visuellt område för levelinteger
    levelLabel = new QLabel();
    levelLabel->setAlignment(Qt::AlignCenter);
    levelLabel->setStyleSheet("font-size: 20px; color : #5296A5; background-color: #292929; padding: 20px;");

    //Skapar visuellt område för nästa bits pixmap
    nextPieceLabel = new QLabel();
    nextPieceLabel->setAlignment(Qt::AlignCenter);

    //Skapar knappar
    startButton = new QPushButton(tr("&STARTA"));
    startButton->setFocusPolicy(Qt::NoFocus);

    quitButton = new QPushButton(tr("&AVSLUTA"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    pauseButton = new QPushButton(tr("&PAUSA"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    pauseButton->setVisible(false);

    //Kopplar signaler för knapptryck
    connect(startButton, &QPushButton::clicked,[=](){
        board->startGame();

        startButton->setText("BÖRJA OM");
        pauseButton->setVisible(true);
    });

    connect(quitButton, &QPushButton::clicked,[=](){
        qApp->quit();
    });

    connect(pauseButton, &QPushButton::clicked, [=]() {
        if (board->pauseGame()) {
            pauseButton->setText("STARTA");
        }
        else{
            pauseButton->setText("PAUSA");
        }
    });

    //Kopplar signaler för uppdatering av fönstrets innehåll
    connect(board, &Board::scoreChange, [=](){ scoreLabel->setNum(board->getScore()); });
    connect(board, &Board::levelChange, [=](){ levelLabel->setNum(board->getlvl()); });
    connect(board, &Board::shapePixmapChange, [=](){ nextPieceLabel->setPixmap(board->getShapePixmap()); });

    //Skapar en header
    std::unique_ptr<QLabel> header = std::make_unique<QLabel>();
    header->setPixmap(QPixmap(R"(C:\Users\angel\OneDrive\Dokument\DT049G\project\tetris.png)"));

    //Sätter alla objekt som widgets i en QGridLayout
    layout->addWidget(header.release(), 0, 0);

    layout->addWidget(startButton, 1, 0);
    layout->addWidget(quitButton, 5, 0);
    layout->addWidget(pauseButton, 2, 0);

    layout->addWidget(nextPieceLabel, 1, 1);
    layout->addWidget(scoreLabel, 3, 1);
    layout->addWidget(levelLabel, 5, 1);

    layout->addWidget(new QLabel("NÄSTA BIT"), 0, 1);
    layout->addWidget(new QLabel("POÄNG"), 2, 1);
    layout->addWidget(new QLabel("LEVEL"), 4, 1);

    layout->addWidget(board, 0, 2, 6, 1);

    //Släpper alla objekt från QGridLayout till fönstret
    setLayout(layout.release());
    setWindowTitle(tr("===Tetris==="));

    //Fönstret har en fast storlek
    setMinimumSize(650, 400);
    setMaximumSize(650, 400);
}

Window::~Window() {
    delete ui;
}

