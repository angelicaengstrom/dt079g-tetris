/*!
 * @file Board.h
 *
 * @brief board.h definerar klassen Board
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */

#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include <QFrame>
#include <QLabel>
#include <QRandomGenerator>
#include <QBasicTimer>
#include "Shape.h"

//! Ett struct predikat
struct comparer{
    /*!
     * Överlagrar funktionsoperatorn som används som predikat till att definera den hierarkiska ordningen för objektet QPoint.
     * Här jämförs QPoint i växande x-positioner och därefter i växande y-positioner
     * @param pointA en QPoint
     * @param pointB en QPoint
     * @return bool
     */
    bool operator()(const QPoint& pointA, const QPoint& pointB) const {
        if (pointA.y() == pointB.y()) {
            return pointA.x() < pointB.x();
        }
        return pointA.y() < pointB.y();
    }
};

/*!
 * @class Board
 *
 * Board är en subklass av QFrame och är till för att definera spelbrädets uppbyggnad.
 * Definerar Q_OBJECT för att använda signaler
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */
class Board: public QFrame {
    Q_OBJECT
public:
    //! Konstruerare
    /*!
     * @param parent en QWidget som defineras nullptr för att denna klass ska vara en top-level QFrame
     */
    explicit Board(QWidget *parent = nullptr);

    //! Medlemsfunktion
    void startGame();

    //! Medlemsfunktion
    bool pauseGame();

    //! Medlemsfunktion
    [[nodiscard]] int getScore() const{ return score; }

    //! Medlemsfunktion
    [[nodiscard]] int getlvl() const{ return lvl; }

    //!Medlemsfunktion
    QPixmap getShapePixmap(){ return nextShape.pixmap(); }

    signals:
    //! Signal
    /*!
     * Startar när spelpoängen ska uppdateras i huvudfönstret
     */
    void scoreChange();

    //! Signal
    /*!
     * Startar när spelets nivå ska uppdateras i huvudfönstret
     */
    void levelChange();

    //! Signal
    /*!
     * Startar när bilden på nästa tetrisbit ska uppdateras i huvudfönstret
     */
    void shapePixmapChange();

protected:
    //! Virtuell funktion från QFrame
    void paintEvent(QPaintEvent* event) override;

    //! Virtuell funktion från QFrame
    void keyPressEvent(QKeyEvent *event) override;

    //! Virtuell funktion från QFrame
    void timerEvent(QTimerEvent *event) override;
private:
    //! En enum
    /*!
    * Size är till för att ge en mer lättläst kod av hur stora tetrisbitar som får plats på bredd och höjd i rutan
    */
    enum Size { Width = 10, Height = 20 };

    //! Privat medlemsfunktion
    /*!
     * @return int, antalet pixlar breddstorlek ett block från huvud-fönstret representerar
     */
    int getBlockWidth(){ return frameRect().width() / Width; }

    //! Privat medlemsfunktion
    /*!
     * @return int, antalet pixlar höjdstorlek ett block från huvud-fönstret representerar
     */
    int getBlockHeight(){ return frameRect().height() / Height; }

    //! Privat medlemsfunktion
    /*!
     * Returnerar en enum shapes beroende på vilken plats som anges på brädet
     * @param location en QPoint som erhåller indexet till brädet
     * @return shapes, en enum som erhåller olika figurer
     */
    shapes shapeAt(QPoint location){ return board[location]; }

    //! Privat medlemsfunktion
    static QColor getShapeColor(shapes s);

    //! Privat medlemsfunktion
    void clearBoard();

    //! Privat medlemsfunktion
    void moveShape(::Shape newShape, QPoint location);

    //! Privat medlemsfunktion
    void setShapeOnBoard();

    //! Privat medlemsfunktion
    void removeLines();

    //! Privat medlemsfunktion
    void addShape();

    //! Privat medlemsfunktion
    void dropShapeToGround();

    //! Privat medlemsfunktion
    void showNextShape();

    //! Privat medlemsfunktion
    void gameOver();

    //! Privat medlemsfunktion
    /*!
     * Estimerar hur lång tid spelets timer ska gå, vilket blir mindre ju högre level spelaren är på
     * @return int, erhåller tiden i ms
     */
    [[nodiscard]] int time() const{ return 500 / lvl; }

    QBasicTimer timer; /*!< spelets timer */

    std::vector<::Shape> dropped_shapes; /*!< erhåller alla figurer som har släppts under spelets gång*/

    QPoint currPos; /*!< erhåller positionen på den fallande figuren */

    QLabel nextShape; /*!< erhåller en ruta vars pixmap representerar nästa figur */

    bool isStarted; /*!< beskriver tillståndet för spelet */
    bool isPaused; /*!< beskriver tillståndet för spelet */
    bool isGameOver; /*!< beskriver tillståndet för spelet */

    int lvl; /*!< erhåller spelets level  */
    int score; /*!< erhåller spelets totala poäng */

    std::map<QPoint, shapes, comparer> board; /*!< beskriver alla figurer som sitter på det nuvarande brädets olika positioner */
};


#endif //PROJECT_BOARD_H
