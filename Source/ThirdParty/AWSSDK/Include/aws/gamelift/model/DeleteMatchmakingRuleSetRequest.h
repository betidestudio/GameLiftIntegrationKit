﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/gamelift/GameLift_EXPORTS.h>
#include <aws/gamelift/GameLiftRequest.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <utility>

namespace Aws
{
namespace GameLift
{
namespace Model
{

  /**
   */
  class DeleteMatchmakingRuleSetRequest : public GameLiftRequest
  {
  public:
    AWS_GAMELIFTINTEGRATIONKIT_API DeleteMatchmakingRuleSetRequest();

    // Service request name is the Operation name which will send this request out,
    // each operation should has unique request name, so that we can get operation's name from this request.
    // Note: this is not true for response, multiple operations may have the same response name,
    // so we can not get operation's name from response.
    inline virtual const char* GetServiceRequestName() const override { return "DeleteMatchmakingRuleSet"; }

    AWS_GAMELIFTINTEGRATIONKIT_API Aws::String SerializePayload() const override;

    AWS_GAMELIFTINTEGRATIONKIT_API Aws::Http::HeaderValueCollection GetRequestSpecificHeaders() const override;


    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline const Aws::String& GetName() const{ return m_name; }

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline bool NameHasBeenSet() const { return m_nameHasBeenSet; }

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline void SetName(const Aws::String& value) { m_nameHasBeenSet = true; m_name = value; }

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline void SetName(Aws::String&& value) { m_nameHasBeenSet = true; m_name = std::move(value); }

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline void SetName(const char* value) { m_nameHasBeenSet = true; m_name.assign(value); }

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline DeleteMatchmakingRuleSetRequest& WithName(const Aws::String& value) { SetName(value); return *this;}

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline DeleteMatchmakingRuleSetRequest& WithName(Aws::String&& value) { SetName(std::move(value)); return *this;}

    /**
     * <p>A unique identifier for the matchmaking rule set to be deleted. (Note: The
     * rule set name is different from the optional "name" field in the rule set body.)
     * You can use either the rule set name or ARN value.</p>
     */
    inline DeleteMatchmakingRuleSetRequest& WithName(const char* value) { SetName(value); return *this;}

  private:

    Aws::String m_name;
    bool m_nameHasBeenSet = false;
  };

} // namespace Model
} // namespace GameLift
} // namespace Aws
