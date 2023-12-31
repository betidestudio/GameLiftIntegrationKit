/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/gamelift/GameLift_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>

namespace Aws
{
namespace GameLift
{
namespace Model
{
  enum class ComputeStatus
  {
    NOT_SET,
    PENDING,
    ACTIVE,
    TERMINATING
  };

namespace ComputeStatusMapper
{
AWS_GAMELIFTINTEGRATIONKIT_API ComputeStatus GetComputeStatusForName(const Aws::String& name);

AWS_GAMELIFTINTEGRATIONKIT_API Aws::String GetNameForComputeStatus(ComputeStatus value);
} // namespace ComputeStatusMapper
} // namespace Model
} // namespace GameLift
} // namespace Aws
