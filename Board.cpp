/*!
 * @file Board.cpp
 *
 * @brief Board.cpp implementerar klassen Board
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */

#include "Board.h"
#include <algorithm>
#include <QPainter>
#include <QKeyEvent>

//! Global funktion
/*!
 * Sätter en random figur på Shape s och returnerar denna
 * @return s, en Shape
 */
Shape generateRandomShape(){
    Shape s;
    s.setShape(shapes(QRandomGenerator::global()->bounded(7) + 1));
    return s;
}

Board::Board(QWidget *parent): QFrame(parent), isStarted(false), isPaused(false), isGameOver(false), lvl(1), score(0) {
    //Sätter stilen för brädrutan
    setFrameShape(QFrame::WinPanel);
    setStyleSheet({"color: #373737;"});
    setFocusPolicy(Qt::StrongFocus);
}

/*!
 * En funktion som överskrider superklassens paintEvent. Brädet formatteras i olika designs beroende på speltillstånd.
 * @param event
 */
void Board::paintEvent(QPaintEvent* event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    //Sätter bakgrunden till brädet som svart
    painter.fillRect(contentsRect(), 0x292929);

    if(isPaused){
        //Skriver ut en text på brädet om spelet är pausat
        painter.fillRect(contentsRect(), 0x292929);
        painter.setPen(0x66CCCC);
        painter.drawText(contentsRect(), Qt::AlignCenter, tr("█ █"));
    }

    if(isStarted && !isPaused) {
        //Går igenom alla figurer som existerar på brädet
        for (auto & it : board) {
            int x = it.first.x();
            int y = it.first.y();
            if (it.second != Empty) {
                //Har brädet en figur, dvs inte Empty, kommer figurens färg att målas på den position korrisponderat
                //med huvud-fönstrets storlek, vilket resulterar i en fyrkant
                painter.fillRect(x * getBlockWidth() + 1, y * getBlockHeight() + 1, getBlockWidth() - 1,
                                 getBlockHeight() - 1,
                                 getShapeColor(it.second));
            } else {
                painter.fillRect(x * getBlockWidth() + 1, y * getBlockHeight() + 1, getBlockWidth(), getBlockHeight(),
                0x292929);
            }
        }
        //Den fallande biten är ännu inte satt på brädet, men målas ut ändå på dess nuvarande positioner
        ::Shape currShape = dropped_shapes.front();
        for (int i = 0; i < 4; i++) {
            int x = currPos.x() + currShape.getCoords()[i].x();
            int y = currPos.y() + currShape.getCoords()[i].y();
            painter.fillRect(x * getBlockWidth() + 1, y * getBlockHeight() + 1, getBlockWidth() - 1,
                             getBlockHeight() - 1,
                             getShapeColor(currShape.getShape()));
        }
    }

    if(isGameOver){
        //Skriver ut en text på brädet om spelet är förlorat
        painter.fillRect(contentsRect(), 0x292929);
        painter.setPen(0x66CCCC);
        painter.drawText(contentsRect(), Qt::AlignCenter, tr("G A M E\nO V E R"));
    }
}
/*!
 * Sätter alla bitar på brädet som empty, dvs ingen figur.
 */
void Board::clearBoard() {
    for(int y = 0; y <= Height; y++){
        for(int x = 0; x < Width; x++){
            board[QPoint(x, y)] = Empty;
        }
    }
}

/*!
 * Hämtar ett färgobjekt, QColor, som används till PaintEvent beroende på enumet shapes s innehåll.
 * @param s enumet shapes
 * @return QColor, ett färgobjekt
 */
QColor Board::getShapeColor(shapes s) {
    if(s == I_shape){ return 0xCC6666; }
    else if(s == J_shape){ return 0x66CC66; }
    else if(s == T_shape){ return 0x6666CC; }
    else if(s == L_shape){ return 0xCCCC66; }
    else if(s == O_shape){ return 0xCC66CC; }
    else if(s == Z_shape){ return 0x66CCCC; }
    else { return 0xDAAA00; }
}

/*!
 * Tar parameter för en Shape och en QPoint, kollar i en for-sats om positionen för QPoint är tillgänglig.
 * Om inte kastas ett fel. Annars uppdateras den nuvarande positionen och den nuvarande fallande biten.
 * @param newShape  en Shape
 * @param location  en QPoint
 */
void Board::moveShape(::Shape newShape, QPoint location) {
    for(int i = 0; i < 4; i++){
        QPoint newPos = location + newShape.getCoords()[i];
        //Om den nya positionen är utanför höjden eller bredden
        if(newPos.y() > Height || newPos.x() < 0 || newPos.x() >= Width){
            throw std::out_of_range("Out of range");
        }
        //Om den nya positionen inte erhåller enumet Empty
        if(shapeAt(newPos) != Empty){
            throw std::out_of_range("Out of range");
        }
    }

    //Uppdaterar figur och plats
    dropped_shapes.front() = newShape;
    currPos = location;
    update();
}

/*!
 * En funktion som överskrider superklassens keyPressEvent lyssnare.
 * Olika handlingar utförs beroende på knapp som har tryckts.
 * @param event
 */
void Board::keyPressEvent(QKeyEvent *event) {
    if(isStarted && !isPaused) {
        switch (event->key()) {
            case Qt::Key_S:
                try {
                    if(dropped_shapes.front().getShape() != O_shape){
                        //Byter ut den fallande figuren till en roterad höger version på brädet
                    moveShape(dropped_shapes.front().rotate_right(), QPoint(currPos.x(), currPos.y())); }
                } catch (std::out_of_range &e) { }
                break;
            case Qt::Key_A:
                try {
                    //Flyttar den fallande figuren till en vänster position på brädet
                    moveShape(dropped_shapes.front(), QPoint(currPos.x() - 1, currPos.y()));
                } catch (std::out_of_range &e) {}
                break;
            case Qt::Key_D:
                try {
                    //Flyttar den fallande figuren till en höger position på brädet
                    moveShape(dropped_shapes.front(), QPoint(currPos.x() + 1, currPos.y()));
                } catch (std::out_of_range &e) { }
                break;
            case Qt::Key_W:
                try {
                    if(dropped_shapes.front().getShape() != O_shape) {
                        //Byter ut den fallande figuren till en roterad vänster version på brädet
                        moveShape(dropped_shapes.front().rotate_left(), QPoint(currPos.x(), currPos.y()));
                    }
                } catch (std::out_of_range &e) { }
                break;
            case Qt::Key_Space:
                //Sätter den nuvarande biten till botten av brädet
                dropShapeToGround();
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
    else{
        QWidget::keyPressEvent(event);
    }
}
/*!
 * En funktion som överskrider superklassens timerEvent lyssnare.
 * Har event parametern samma id som spelets timer utförs en flyttning av den nuvarande figuren till en nedåt position i brädet
 * @param event
 */
void Board::timerEvent(QTimerEvent *event) {
    if(event->timerId() == timer.timerId()){
        try{
            //Flyttar den nuvarande figuren nedåt
            moveShape(dropped_shapes.front(), QPoint(currPos.x(), currPos.y() + 1));
        }catch (std::out_of_range& e){
            //Sätter fast den nuvarande figuren på brädet
            setShapeOnBoard();
            //Byter plats så att nästa bit blir den nuvarande biten, dvs längst fram
            std::swap(dropped_shapes.front(), dropped_shapes.back());
            addShape();
        }
    }
    else {
        QObject::timerEvent(event);
    }
}
/*!
 * En funktion som exekverar vid knapptryck på pausknappen. Detta stoppar spelets timer.
 * Vid knapptryck igen startar spelets timer. Returvärdet returnerar tillståndet, dvs om spelet är pausat eller inte.
 * @return bool, returnerar om spelet är pausat eller inte
 */
bool Board::pauseGame() {
    isPaused = !isPaused; //Vid knapptryck blir den tvärtemot
    if(isPaused){
        timer.stop(); //Stannar timern
        update(); //Uppdaterar skärmen
        return true;
    }
    else{
        timer.start(time(), this); //startar timern igen
        update(); //Uppdaterar skärmen
        return false;
    }
}

/*!
 * En funktion som exekverar vid knapptryck på startknappen. Denna funktion sätter upp ett nytt spel,
 * genom att tömma brädet och återställa level samt score. Sedan startas timern och spelet börjar exekvera.
 */
void Board::startGame() {
    clearBoard();
    dropped_shapes.clear();

    dropped_shapes.push_back(generateRandomShape());

    lvl = 1;
    score = 0;
    isStarted = true;
    isPaused = false;
    isGameOver = false;

    emit scoreChange();
    emit levelChange();

    addShape();
    timer.start(time(), this);
}

/*!
 * Adderar en ny figur och återställer dess nuvarande position till startpositionen. Om det kastas ett fel vid flytt
 * till startpositionen är spelet förlorat.
 */
void Board::addShape() {
    try {
        currPos = QPoint(Width / 2, 0);
        dropped_shapes.push_back(generateRandomShape());
        showNextShape();
        //Lägger till den nya figuren på startpositionen
        moveShape(dropped_shapes.front(),currPos);
    }catch(std::out_of_range& e){
        gameOver();
    }
}

/*!
 * Flyttar den nuvarande figuren nedåt tills att det inte går att flytta den mer.
 */
void Board::dropShapeToGround() {
    while(true) {
        try {
            moveShape(dropped_shapes.front(), QPoint(currPos.x(), currPos.y() + 1));
        }
        catch (std::out_of_range& e){
            break;
        }
    }
}

/*!
 * Lägger till den nuvarande figuren fast på brädet med dess korrisponderande koordinater till brädet.
 * Kollar oxå efter ditsättningen om antalet figurer under spelets gång är jämt delbar med 10.
 * Om sant ökas nivån och spelets timer uppdateras.
 */
void Board::setShapeOnBoard() {
    for (int i = 0; i < 4; i++) {
        board[currPos + dropped_shapes.front().getCoords()[i]] = dropped_shapes.front().getShape();
    }
    removeLines();

    if(dropped_shapes.size() % 10 == 0){
        lvl++;
        timer.start(time(),this);
        emit levelChange();
    }
}

/*!
 * Kollar om det finns figurer på en hela bredden på brädet.
 * Om sant tas bredden bort till dess övre figurer och spelarens poäng ökas.
 */
void Board::removeLines() {
    int fullLines = 0;
    for(int y = 0; y <= Height; y++){
        bool isFull = true;
        for(int x = 0; x < Width; x++){
            if(board[QPoint(x,y)] == Empty){
                isFull = false;
                break;
            }
        }
        if(isFull){
            ++fullLines;
            for(int _y = y; _y > 0; _y--){
                for(int x = 0; x < Width; x++){
                    board[QPoint(x, _y)] = shapeAt(QPoint(x, _y - 1));
                }
            }
        }
    }
    if(fullLines > 0){
        score += 10 * fullLines;
        emit scoreChange();
    }
}

/*!
 * Sätter en pixmap beroende på vad nästa bit är för figur, med dess korrisponderande färger och koordinater.
 */
void Board::showNextShape() {
    ::Shape next = dropped_shapes.back();
    QPixmap pixmap(getBlockWidth() * 4, getBlockHeight() * 4);
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), QColor(0x373737));
    for(int i = 0; i < 4; i++) {
        int x = next.getCoords()[i].x();
        int y = next.getCoords()[i].y();
        painter.fillRect(x * getBlockWidth() + 30, y * getBlockHeight() + 1, getBlockWidth() - 1, getBlockHeight() - 1,
                         getShapeColor(next.getShape()));
    }
    nextShape.setPixmap(pixmap);
    nextShape.setStyleSheet({"background-color: #373737;"});
    emit shapePixmapChange();
}

/*!
 * Om spelet är förlorat stoppas speltimern
 */
void Board::gameOver() {
    isStarted = false;
    isGameOver = true;
    timer.stop();
    nextShape.clear();
    shapePixmapChange();
    update();

    qDebug() << "GAME OVER";
}


