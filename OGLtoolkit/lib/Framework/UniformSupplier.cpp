#include "UniformSupplier.h"
#include <algorithm>
#include "lib/Utils/Debug.h"

/** Определение имен uniform-переменных
  */
string UniformSupplier::ViewMatrixName = "_V";
string UniformSupplier::InverseViewMatrixName = "_InvV";
string UniformSupplier::ModelMatrixName = "_M";
string UniformSupplier::NormalMatrixName = "_N";
string UniformSupplier::ModelViewMatrixName = "_MV";
string UniformSupplier::ModelViewProjectionMatrixName = "_MVP";

string UniformSupplier::TimeValueName = "_time";
string UniformSupplier::WindowSizeName = "_winSize";

void UniformSupplier::calculateFlags(GpuProgram *program) {
        StringList uniformList = program->activeUniforms();
        int uniformPositions[] = {
                AutoUniforms::ViewMatrix,
                AutoUniforms::InverseViewMatrix,
                AutoUniforms::ModelMatrix,
                AutoUniforms::NormalMatrix,
                AutoUniforms::ModelViewMatrix,
                AutoUniforms::ModelViewProjectionMatrix,
                AutoUniforms::TimeValue,
                AutoUniforms::WindowSize
        };
        string uniformNames[] = {
                ViewMatrixName,
                InverseViewMatrixName,
                ModelMatrixName,
                NormalMatrixName,
                ModelViewMatrixName,
                ModelViewProjectionMatrixName,
                TimeValueName,
                WindowSizeName,
        };

        for(size_t i=0; i<m_flags.size(); ++i) {
                // Проверяем, есть ли в списке имя
                if(std::find(uniformList.begin(), uniformList.end(), uniformNames[i]) != uniformList.end()) {
                        m_flags.set(uniformPositions[i]);
                }
        }
}
