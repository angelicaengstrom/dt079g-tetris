#ifndef PROJECT_SHAPE_H
#define PROJECT_SHAPE_H
/*!
 * @file Shape.h
 *
 * @brief Shape.h definerar klassen Shape
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */
#include <QPoint>

//! En enum
/*!
 * shapes är till för att ge en mer lättläst kod av de olika formerna en tetrisbit kan ha
 */
enum shapes{Empty, I_shape, J_shape, L_shape, O_shape, S_shape, T_shape, Z_shape};

/*!
 * @class Shape
 *
 * Shape föreställer en tetrisbit med varierande form och dess korresponderande koordinater
 *
 * @author Angelica Engström
 * Contact: angelica.princess@hotmail.com
 */
class Shape {
public:
    //! Konstruerare
    /*!
     * Sätter alltid tetrisbitens form som enum shapes variabeln Empty, dvs ingen form
     */
    Shape():figure(Empty){ setShape(Empty); };

    //! Medlems funktion
    /*!
     * Beroende på fig tilldelas instansens privata attribut en figur med figurens korrisponderande koordinater
     * @param fig
     */
    void setShape(enum shapes fig);

    //! Medlems funktion
    /*!
     * Hämtar instansen privata medlem figure, en enum som representerar instansens figur
     * @return figure, en enum variabel shapes
     */
    shapes getShape(){ return figure; }

    //! Medlems funktion
    /*!
     * Hämtar instansens privata medlem coords, en QPoint array som erhåller tetrisbitarnas positioner
     * @return coords, en QPoint array
     */
    [[nodiscard]] const QPoint* getCoords() const { return coords; };

    //! Medlems funktion
    [[nodiscard]] Shape rotate_right() const;

    //! Medlems funktion
    [[nodiscard]] Shape rotate_left() const;
private:
    //! Enum variabel
    shapes figure; /*!< beskriver instansens figur */

    QPoint coords[4]; /*!< beskriver instansens koordinater */
};


#endif //PROJECT_SHAPE_H
