#ifndef UNIFORMSUPPLIER_H
#define UNIFORMSUPPLIER_H

#include <string>
#include <bitset>
#include "lib/Core/OpenGL/GpuProgram.h"

using namespace std;

namespace AutoUniforms {
enum Enum {
        ViewMatrix,
        InverseViewMatrix,
        ModelMatrix,
        NormalMatrix,
        ModelViewMatrix,
        ModelViewProjectionMatrix,
        TimeValue,
        WindowSize,

        COUNT
};
}

/** Служит для автоматического обеспечения шейдера uniform-переменными
  * Имена автоматически передаваемых переменных указаны ниже.
  * Каждый автоматически передаваемый аттрибут или переменная имеет синтаксис "_ИмяПеременной"
  */
class UniformSupplier {
private:
        // Флаги, обозначающие нужно ли передавать uniform-переменную
        bitset<AutoUniforms::COUNT>     m_flags;

public:
        static const string ViewMatrixName;
        static const string InverseViewMatrixName;

        static const string ModelMatrixName;
        static const string NormalMatrixName;

        static const string ModelViewMatrixName;
        static const string ModelViewProjectionMatrixName;

        static const string TimeValueName;
        static const string WindowSizeName;

public:
        // Определяет нужно ли передавать значение такой переменной
        bool    isNeedSupplyUniform(AutoUniforms::Enum uniform)           { return m_flags.test(uniform); }

        // По шейдеру, узнает какие uniform нужны шейдеру
        void    calculateFlags(GpuProgram* program);
};

/** Определение имен uniform-переменных
  */
const string UniformSupplier::ViewMatrixName = "_ViewMatrix";
const string UniformSupplier::InverseViewMatrixName = "_InverseViewMatrix";
const string UniformSupplier::ModelMatrixName = "_ModelMatrix";
const string UniformSupplier::NormalMatrixName = "_NormalMatrix";
const string UniformSupplier::ModelViewMatrixName = "_ModelViewMatrix";
const string UniformSupplier::ModelViewProjectionMatrixName = "_ModelViewProjectionMatrix";

const string UniformSupplier::TimeValueName = "_time";
const string UniformSupplier::WindowSizeName = "_windowSize";



#endif // UNIFORMSUPPLIER_H
