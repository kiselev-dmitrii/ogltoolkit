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
  * Имена автоматически передаваемых переменных указаны в *.cpp файле.
  * Каждый автоматически передаваемый аттрибут или переменная имеет синтаксис "_ИмяПеременной"
  */
class UniformSupplier {
private:
        // Флаги, обозначающие нужно ли передавать uniform-переменную
        bitset<AutoUniforms::COUNT>     m_flags;

public:
        static string ViewMatrixName;
        static string InverseViewMatrixName;

        static string ModelMatrixName;
        static string NormalMatrixName;

        static string ModelViewMatrixName;
        static string ModelViewProjectionMatrixName;

        static string TimeValueName;
        static string WindowSizeName;

public:
        // Определяет нужно ли передавать значение такой переменной
        bool    isNeedSupplyUniform(AutoUniforms::Enum uniform)           { return m_flags.test(uniform); }

        // По шейдеру, узнает какие uniform нужны шейдеру
        void    calculateFlags(GpuProgram* program);
};


#endif // UNIFORMSUPPLIER_H
