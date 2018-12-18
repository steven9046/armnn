﻿//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "Permute.hpp"

#include "Half.hpp"
#include <armnn/Tensor.hpp>

#include <cassert>
#include <cstring>

namespace
{

class PermuteLoop
{
public:
    using size_type = unsigned int;

    PermuteLoop(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings)
        : m_DstShape(dstShape)
    {
        assert(dstShape.GetNumDimensions() == mappings.GetSize());

        const size_type numDims = dstShape.GetNumDimensions();

        size_type srcStride = 1U;
        size_type dstStride = 1U;

        for (size_type i = numDims - 1U, k = 0U; k < numDims; ++k, --i)
        {
            m_SrcStrides[mappings[i]] = srcStride;
            m_DstStrides[i] = dstStride;

            srcStride *= dstShape[mappings[i]];
            dstStride *= dstShape[i];
        }
    }

    template <typename T>
    void Unroll(const T* srcData, T* dstData)
    {
        const T* const srcEnd = srcData + m_DstShape.GetNumElements();
        T* const       dstEnd = dstData + m_DstShape.GetNumElements();
        Unroll(0, srcData, dstData, srcEnd, dstEnd);
    }

    void Unroll(const void* srcData, void* dstData, size_t dataTypeSize)
    {
        assert(srcData);
        assert(dstData);
        assert(dataTypeSize > 0);

        const unsigned char* srcDataPtr = reinterpret_cast<const unsigned char*>(srcData);
        unsigned char* dstDataPtr       = reinterpret_cast<unsigned char*>(dstData);

        const unsigned char* const srcEndPtr = srcDataPtr + m_DstShape.GetNumElements() * dataTypeSize;
        unsigned char* const       dstEndPtr = dstDataPtr + m_DstShape.GetNumElements() * dataTypeSize;

        Unroll(0, srcDataPtr, dstDataPtr, srcEndPtr, dstEndPtr, dataTypeSize);
    }

private:
    template <typename T>
    void Unroll(size_type dimension, const T* srcData, T* dstData, const T* srcEnd, T* dstEnd)
    {
        assert(srcData);
        assert(dstData);
        assert(srcEnd);
        assert(dstEnd);
        assert(srcData < srcEnd);
        assert(dstData < dstEnd);

        if (dimension >= m_DstShape.GetNumDimensions())
        {
            *dstData = *srcData;
        }
        else
        {
            for (size_type i = 0; i < m_DstShape[dimension]; i++)
            {
                Unroll(dimension + 1, srcData, dstData, srcEnd, dstEnd);

                srcData += m_SrcStrides[dimension];
                dstData += m_DstStrides[dimension];
            }
        }
    }

    void Unroll(size_type dimension,
                const unsigned char* srcData, unsigned char* dstData,
                const unsigned char* srcEnd, unsigned char* dstEnd,
                size_t dataTypeSize)
    {
        assert(srcData);
        assert(dstData);
        assert(srcEnd);
        assert(dstEnd);
        assert(srcData < srcEnd);
        assert(dstData < dstEnd);
        assert(dataTypeSize > 0);

        if (dimension >= m_DstShape.GetNumDimensions())
        {
            ::memcpy(dstData, srcData, dataTypeSize);
        }
        else
        {
            for (size_type i = 0; i < m_DstShape[dimension]; i++)
            {
                Unroll(dimension + 1, srcData, dstData, srcEnd, dstEnd, dataTypeSize);

                srcData += m_SrcStrides[dimension] * dataTypeSize;
                dstData += m_DstStrides[dimension] * dataTypeSize;
            }
        }
    }

    armnn::TensorShape m_DstShape;
    std::array<size_type, armnn::MaxNumOfTensorDimensions> m_SrcStrides;
    std::array<size_type, armnn::MaxNumOfTensorDimensions> m_DstStrides;
};

} // namespace

namespace armnnUtils
{

armnn::TensorShape Permuted(const armnn::TensorShape& srcShape, const armnn::PermutationVector& mappings)
{
    assert(srcShape.GetNumDimensions() == mappings.GetSize());

    const unsigned int numDims = mappings.GetSize();
    unsigned int outDims[armnn::MaxNumOfTensorDimensions];

    for (unsigned int i = 0U; i < numDims; ++i)
    {
        outDims[mappings[i]] = srcShape[i];
    }

    armnn::TensorShape permutedShape(numDims, outDims);
    return permutedShape;
}

armnn::TensorInfo Permuted(const armnn::TensorInfo& info, const armnn::PermutationVector& mappings)
{
    armnn::TensorInfo outInfo(info);
    outInfo.SetShape(Permuted(info.GetShape(), mappings));
    return outInfo;
}

void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings,
             const void* src, void* dst, size_t dataTypeSize)
{
    PermuteLoop(dstShape, mappings).Unroll(src, dst, dataTypeSize);
}

template <typename T>
void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings, const T* src, T* dst)
{
    PermuteLoop(dstShape, mappings).Unroll(src, dst);
}

// Instantiates for types.
template void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings,
                      const armnn::Half* src, armnn::Half* dst);
template void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings,
                      const float* src, float* dst);
template void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings,
                      const uint8_t* src, uint8_t* dst);
template void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings,
                      const int32_t* src, int32_t* dst);
template void Permute(const armnn::TensorShape& dstShape, const armnn::PermutationVector& mappings,
                      const bool* src, bool* dst);

} // namespace armnnUtils
