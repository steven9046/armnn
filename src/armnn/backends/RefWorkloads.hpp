//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#pragma once

#include "backends/RefWorkloads/RefConstantUint8Workload.hpp"
#include "backends/RefWorkloads/Addition.hpp"
#include "backends/RefWorkloads/ConvImpl.hpp"
#include "backends/RefWorkloads/RefMultiplicationUint8Workload.hpp"
#include "backends/RefWorkloads/RefBaseConstantWorkload.hpp"
#include "backends/RefWorkloads/RefConvolution2dUint8Workload.hpp"
#include "backends/RefWorkloads/RefSplitterUint8Workload.hpp"
#include "backends/RefWorkloads/RefResizeBilinearUint8Workload.hpp"
#include "backends/RefWorkloads/RefL2NormalizationFloat32Workload.hpp"
#include "backends/RefWorkloads/Multiplication.hpp"
#include "backends/RefWorkloads/RefActivationUint8Workload.hpp"
#include "backends/RefWorkloads/RefPooling2dFloat32Workload.hpp"
#include "backends/RefWorkloads/RefWorkloadUtils.hpp"
#include "backends/RefWorkloads/RefMergerUint8Workload.hpp"
#include "backends/RefWorkloads/RefFullyConnectedFloat32Workload.hpp"
#include "backends/RefWorkloads/Softmax.hpp"
#include "backends/RefWorkloads/RefMergerFloat32Workload.hpp"
#include "backends/RefWorkloads/TensorBufferArrayView.hpp"
#include "backends/RefWorkloads/RefBatchNormalizationFloat32Workload.hpp"
#include "backends/RefWorkloads/Splitter.hpp"
#include "backends/RefWorkloads/RefFullyConnectedUint8Workload.hpp"
#include "backends/RefWorkloads/RefReshapeFloat32Workload.hpp"
#include "backends/RefWorkloads/RefDepthwiseConvolution2dUint8Workload.hpp"
#include "backends/RefWorkloads/FullyConnected.hpp"
#include "backends/RefWorkloads/RefFloorFloat32Workload.hpp"
#include "backends/RefWorkloads/RefSoftmaxFloat32Workload.hpp"
#include "backends/RefWorkloads/RefSoftmaxUint8Workload.hpp"
#include "backends/RefWorkloads/RefReshapeUint8Workload.hpp"
#include "backends/RefWorkloads/RefResizeBilinearFloat32Workload.hpp"
#include "backends/RefWorkloads/RefAdditionUint8Workload.hpp"
#include "backends/RefWorkloads/RefMultiplicationFloat32Workload.hpp"
#include "backends/RefWorkloads/RefBatchNormalizationUint8Workload.hpp"
#include "backends/RefWorkloads/ResizeBilinear.hpp"
#include "backends/RefWorkloads/RefNormalizationFloat32Workload.hpp"
#include "backends/RefWorkloads/RefDepthwiseConvolution2dFloat32Workload.hpp"
#include "backends/RefWorkloads/RefPooling2dUint8Workload.hpp"
#include "backends/RefWorkloads/BatchNormImpl.hpp"
#include "backends/RefWorkloads/Activation.hpp"
#include "backends/RefWorkloads/Merger.hpp"
#include "backends/RefWorkloads/RefSplitterFloat32Workload.hpp"
#include "backends/RefWorkloads/RefConstantFloat32Workload.hpp"
#include "backends/RefWorkloads/RefActivationFloat32Workload.hpp"
#include "backends/RefWorkloads/RefConvolution2dFloat32Workload.hpp"
#include "backends/RefWorkloads/RefAdditionFloat32Workload.hpp"
#include "backends/RefWorkloads/Pooling2d.hpp"
#include "backends/RefWorkloads/RefFakeQuantizationFloat32Workload.hpp"
#include "backends/RefWorkloads/RefPermuteWorkload.hpp"
#include "backends/RefWorkloads/RefLstmFloat32Workload.hpp"
#include "backends/RefWorkloads/RefConvertFp16ToFp32Workload.hpp"
#include "backends/RefWorkloads/RefConvertFp32ToFp16Workload.hpp"
#include "backends/RefWorkloads/RefDivisionFloat32Workload.hpp"
#include "backends/RefWorkloads/RefDivisionUint8Workload.hpp"
