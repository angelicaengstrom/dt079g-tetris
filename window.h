#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H
/*!
 * @file window.h
 *
 * @brief window.h definerar klassen Window
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include "Board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE
/*!
 * @class Window
 *
 * Window är en subklass av QWidget och är till för att definera en layout på spelfönstret.
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */
class Window : public QWidget {
Q_OBJECT

public:
    //! En konstruerare
    /*!
     * @param parent är satt som nullptr då Window ska vara en top-level widget
     */
    explicit Window(QWidget *parent = nullptr);

    //! En destruerare
    ~Window() override;

private:
    Ui::Window *ui;

    QLabel *scoreLabel; /*!< En ruta som visar spelarens poäng i fönstret */
    QLabel *levelLabel; /*!< En ruta som visar spelets level i fönstret */
    QLabel *nextPieceLabel; /*!< En ruta som visar spelets nästa tetrisbit i fönstret */

    QPushButton *startButton; /*!< En knapp som startar spelet*/
    QPushButton *quitButton; /*!< En knapp som stänger ned fönstret */
    QPushButton *pauseButton; /*!< En knapp som pausar spelet */

    Board *board; /*!< Ett spelbräde som visas i fönstret */
};


#endif //PROJECT_WINDOW_H
