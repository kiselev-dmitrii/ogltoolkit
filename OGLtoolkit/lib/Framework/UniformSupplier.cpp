#include "UniformSupplier.h"
#include <algorithm>

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

        for(int i=0; i<m_flags.size(); ++i) {
                // Проверяем, есть ли в списке имя
                if(std::find(uniformList.begin(), uniformList.end(), uniformNames[i]) != uniformList.end()) {
                        m_flags.set(uniformPositions[i]);
                }
        }
}
