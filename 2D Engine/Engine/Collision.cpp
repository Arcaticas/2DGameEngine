#include "Collision.h"

bool Collision::IsColliding(Collidable i_a, Collidable i_b)
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
