#include "Collision.h"

namespace Collision
{
    static std::vector<Collidable>& AllCollidables = *new std::vector<Collidable>();

    bool IsCollidingStatic(Collidable& i_a, Collidable& i_b)
    {
        //Transform Matrixes
        Matrix::Matrix4x4 MARotation = i_a.GetRotationMatrix();
        Matrix::Matrix4x4 MATranslation = i_a.GetTransformationMatrix();

        Matrix::Matrix4x4 MAtoWorld = MATranslation * MARotation;
        Matrix::Matrix4x4 MWorldtoA = MAtoWorld.Invert();

        Matrix::Matrix4x4 MBRotation = i_b.GetRotationMatrix();
        Matrix::Matrix4x4 MBTranslation = i_b.GetTransformationMatrix();

        Matrix::Matrix4x4 MBtoWorld = MBTranslation * MBRotation;
        Matrix::Matrix4x4 MWorldtoB = MBtoWorld.Invert();

        Matrix::Matrix4x4 MAtoB = MWorldtoB * MAtoWorld;
        Matrix::Matrix4x4 MBtoA = MWorldtoA * MBtoWorld;

        //A in B Check
        Matrix::Vector4 AsBBCenterInB = MAtoB * Matrix::Vector4(i_a.GetCenter().getXPosition(), i_a.GetCenter().getYPosition(), 0, 1);

        Matrix::Vector4 AExtentXinB = MAtoB * Matrix::Vector4(i_a.GetExtent().getXPosition(), 0, 0, 0);
        Matrix::Vector4 AExtentYinB = MAtoB * Matrix::Vector4(0, i_a.GetExtent().getYPosition(), 0, 0);

        float AProjectionOntoB_X = fabs(AExtentXinB.GetX()) + fabs(AExtentYinB.GetX());
        float AProjectionOntoB_Y = fabs(AExtentXinB.GetY()) + fabs(AExtentYinB.GetY());

        float AsLeftEdgeInB = AsBBCenterInB.GetX() - AProjectionOntoB_X;
        float AsRightEdgeInB = AsBBCenterInB.GetX() + AProjectionOntoB_X;
        float AsTopEdgeInB = AsBBCenterInB.GetY() - AProjectionOntoB_Y;
        float AsBottomEdgeInB = AsBBCenterInB.GetY() + AProjectionOntoB_Y;

        float BsLeftEdgeInB = i_b.GetCenter().getXPosition() - i_b.GetExtent().getXPosition();
        float BsRightEdgeInB = i_b.GetCenter().getXPosition() + i_b.GetExtent().getXPosition();
        float BsTopEdgeInB = i_b.GetCenter().getYPosition() - i_b.GetExtent().getYPosition();
        float BsBottomEdgeInB = i_b.GetCenter().getYPosition() + i_b.GetExtent().getYPosition();

        int seperationAxisInB = 2;

        if (i_a.GetCenter().getXPosition() > i_b.GetCenter().getXPosition())
        {
            if (BsRightEdgeInB > AsLeftEdgeInB)
            {
                seperationAxisInB--;
            }
        }
        else
        {
            if (AsRightEdgeInB > BsLeftEdgeInB)
            {
                seperationAxisInB--;
            }
        }

        if (i_a.GetCenter().getYPosition() > i_b.GetCenter().getYPosition())
        {
            if (BsTopEdgeInB > AsBottomEdgeInB)
            {
                seperationAxisInB--;
            }
        }
        else
        {
            if (AsTopEdgeInB > BsBottomEdgeInB)
            {
                seperationAxisInB--;
            }
        }

        if (seperationAxisInB > 0)
        {
            return false;
        }

        //B in A Check
        Matrix::Vector4 BsBBCenterInA = MBtoA * Matrix::Vector4(i_b.GetCenter().getXPosition(), i_b.GetCenter().getYPosition(), 0, 1);

        Matrix::Vector4 BExtentXinA = MBtoA * Matrix::Vector4(i_b.GetExtent().getXPosition(), 0, 0, 0);
        Matrix::Vector4 BExtentYinA = MBtoA * Matrix::Vector4(0, i_b.GetExtent().getYPosition(), 0, 0);

        float BProjectionOntoA_X = fabs(BExtentXinA.GetX()) + fabs(BExtentXinA.GetX());
        float BProjectionOntoA_Y = fabs(BExtentYinA.GetY()) + fabs(BExtentYinA.GetY());

        float BsLeftEdgeInA = BsBBCenterInA.GetX() - BProjectionOntoA_X;
        float BsRightEdgeInA = BsBBCenterInA.GetX() + BProjectionOntoA_X;
        float BsTopEdgeInA = BsBBCenterInA.GetY() - BProjectionOntoA_Y;
        float BsBottomEdgeInA = BsBBCenterInA.GetY() + BProjectionOntoA_Y;

        float AsLeftEdgeInA = i_a.GetCenter().getXPosition() - i_a.GetExtent().getXPosition();
        float AsRightEdgeInA = i_a.GetCenter().getXPosition() + i_a.GetExtent().getXPosition();
        float AsTopEdgeInA = i_a.GetCenter().getYPosition() - i_a.GetExtent().getYPosition();
        float AsBottomEdgeInA = i_a.GetCenter().getYPosition() + i_a.GetExtent().getYPosition();

        int seperationAxisInA = 2;

        if (i_a.GetCenter().getXPosition() > i_b.GetCenter().getXPosition())
        {
            if (BsRightEdgeInA > AsLeftEdgeInA)
            {
                seperationAxisInA--;
            }
        }
        else
        {
            if (AsRightEdgeInA > BsLeftEdgeInA)
            {
                seperationAxisInA--;
            }
        }

        if (i_a.GetCenter().getYPosition() > i_b.GetCenter().getYPosition())
        {
            if (BsTopEdgeInA > AsBottomEdgeInB)
            {
                seperationAxisInA--;
            }
        }
        else
        {
            if (AsTopEdgeInA > BsBottomEdgeInA)
            {
                seperationAxisInA--;
            }
        }

        if (seperationAxisInA > 0)
        {
            return false;
        }

        return true;
    }
    bool IsCollidingSweep(Collidable& i_a, Collidable& i_b, float frameTime)
    {
        //Transform Matrixes
        Matrix::Matrix4x4 MARotation = i_a.GetRotationMatrix();
        Matrix::Matrix4x4 MATranslation = i_a.GetTransformationMatrix();

        Matrix::Matrix4x4 MAtoWorld = MATranslation * MARotation;
        Matrix::Matrix4x4 MWorldtoA = MAtoWorld.Invert();

        Matrix::Matrix4x4 MBRotation = i_b.GetRotationMatrix();
        Matrix::Matrix4x4 MBTranslation = i_b.GetTransformationMatrix();

        Matrix::Matrix4x4 MBtoWorld = MBTranslation * MBRotation;
        Matrix::Matrix4x4 MWorldtoB = MBtoWorld.Invert();

        Matrix::Matrix4x4 MAtoB = MWorldtoB * MAtoWorld;
        Matrix::Matrix4x4 MBtoA = MWorldtoA * MBtoWorld;

        //A in B Check
        Matrix::Vector4 AsBBCenterInB = MAtoB * Matrix::Vector4(i_a.GetCenter().getXPosition(), i_a.GetCenter().getYPosition(), 0, 1);

        Matrix::Vector4 AExtentXinB = MAtoB * Matrix::Vector4(i_a.GetExtent().getXPosition(), 0, 0, 0);
        Matrix::Vector4 AExtentYinB = MAtoB * Matrix::Vector4(0, i_a.GetExtent().getYPosition(), 0, 0);

        float AProjectionOntoB_X = fabs(AExtentXinB.GetX()) + fabs(AExtentYinB.GetX());
        float AProjectionOntoB_Y = fabs(AExtentXinB.GetY()) + fabs(AExtentYinB.GetY());

        float BsLeftEdgeInB = i_b.GetCenter().getXPosition() - i_b.GetExtent().getXPosition();
        float BsRightEdgeInB = i_b.GetCenter().getXPosition() + i_b.GetExtent().getXPosition();
        float BsTopEdgeInB = i_b.GetCenter().getYPosition() - i_b.GetExtent().getYPosition();
        float BsBottomEdgeInB = i_b.GetCenter().getYPosition() + i_b.GetExtent().getYPosition();

        Matrix::Vector4 AsVelocity = i_a.GetVelocity();
        Matrix::Vector4 BsVelocity = i_b.GetVelocity();

        Matrix::Vector4 AsRelativeVelocityToB =  MWorldtoB * (AsVelocity - BsVelocity);

        //X coord check
        float dLeft = (BsLeftEdgeInB - AProjectionOntoB_X) - i_a.GetCenter().getXPosition();
        float dRight = (BsRightEdgeInB + AProjectionOntoB_X) - i_a.GetCenter().getXPosition();

        float tLeft = dLeft / AsRelativeVelocityToB.GetX();
        float tRight = dRight / AsRelativeVelocityToB.GetX();

        float tOpenX;
        float tCloseX;
        if (tLeft < tRight)
        {
            tCloseX = tLeft;
            tOpenX = tRight;
        }
        else
        {
            tCloseX = tRight;
            tOpenX = tLeft;
        }

        //Y coord check
        float dUp = (BsTopEdgeInB - AProjectionOntoB_Y) - i_a.GetCenter().getYPosition();
        float dDown = (BsBottomEdgeInB + AProjectionOntoB_Y) - i_a.GetCenter().getYPosition();

        float tUp = dUp / AsRelativeVelocityToB.GetY();
        float tDown = dDown / AsRelativeVelocityToB.GetY();

        float tOpenY;
        float tCloseY;
        if (tUp < tDown)
        {
            tCloseY = tUp;
            tOpenY = tDown;
        }
        else
        {
            tCloseY = tUp;
            tOpenY = tDown;
        }

        if (tCloseX > frameTime || tCloseY > frameTime)
        {
            return false;
        }
        if (tOpenX < 0 || tOpenY < 0)
        {
            return false;
        }
        if (AsRelativeVelocityToB.GetX() == 0 && (i_a.GetCenter().getXPosition() > (BsRightEdgeInB + AProjectionOntoB_X) || i_a.GetCenter().getXPosition() < (BsLeftEdgeInB - AProjectionOntoB_X)))
        {
            return false;
        }
        if (AsRelativeVelocityToB.GetY() == 0 && (i_a.GetCenter().getYPosition() > (BsBottomEdgeInB + AProjectionOntoB_Y) || i_a.GetCenter().getYPosition() < (BsTopEdgeInB - AProjectionOntoB_Y)))
        {
            return false;
        }

        if (tCloseX < tCloseY)
        {
            if (tCloseY < tOpenX)
            {
                //tCloseY = timeOfCollision
                return true;
            }
        }
        else
        {
            if (tCloseX < tOpenY)
            {
                //tCloseX = timeOfCollision
                return true;
            }
        }
        

        






        return false;
    }

    void Shutdown()
    {
        AllCollidables.clear();
        delete &AllCollidables;
    }
}


