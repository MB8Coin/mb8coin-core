// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2017-2018 The MB8Coin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chain.h"
#include "main.h"
#include "pos.h"
#include "chainparams.h"
#include "primitives/block.h"

double GetDifficulty(const CBlockIndex* blockindex)
{
  // Floating point number that is a multiple of the minimum difficulty,
  // minimum difficulty = 1.0.
  if (blockindex == NULL)
  {
      if (pindexBestHeader == NULL)
          return 1.0;
      else
          blockindex = GetLastBlockIndex(pindexBestHeader, false);
  }

  int nShift = (blockindex->nBits >> 24) & 0xff;

  double dDiff =
      (double)0x0000ffff / (double)(blockindex->nBits & 0x00ffffff);

  while (nShift < 29)
  {
      dDiff *= 256.0;
      nShift++;
  }
  while (nShift > 29)
  {
      dDiff /= 256.0;
      nShift--;
  }

  return dDiff;
}

double GetPoWMHashPS()
{
    return 0;
}

double GetPoSKernelPS()
{
    int nPoSInterval = 72;
    double dStakeKernelsTriedAvg = 0;
    int nStakesHandled = 0, nStakesTime = 0;

    CBlockIndex* pindex = pindexBestHeader;
    CBlockIndex* pindexPrevStake = NULL;

    while (pindex && nStakesHandled < nPoSInterval)
    {
        if (pindex->IsProofOfStake())
        {
            if (pindexPrevStake)
            {
                dStakeKernelsTriedAvg += GetDifficulty(pindexPrevStake) * 4294967296.0;
                nStakesTime += pindexPrevStake->nTime - pindex->nTime;
                nStakesHandled++;
            }
            pindexPrevStake = pindex;
        }

        pindex = pindex->pprev;
    }

    double result = 0;

    if (nStakesTime)
        result = dStakeKernelsTriedAvg / nStakesTime;

    result *= STAKE_TIMESTAMP_MASK + 1;

    return result;
}

int64_t GetProofOfStakeReward(int nHeight, int64_t nCoinAge, int64_t nFees, CBlockIndex* pindexPrev)
{
    auto consensus = Params().GetConsensus();
    int64_t nSubsidy;
    if (consensus.nRewardChangeHeight < 0 || nHeight < consensus.nRewardChangeHeight) {
        nSubsidy = 190 * COIN;
    } else {
        int64_t circulating = pindexPrev->nMoneySupply - pindexPrev->nBurntSupply;
        int nBlocksPerYear = Params().GetConsensus().nDailyBlockCount * 365;
        double nPercentageIncrease = 0.015;
        nSubsidy = (circulating * nPercentageIncrease) / nBlocksPerYear;
    }

    if (nHeight - 1 < 30 * 7 * Params().GetConsensus().nDailyBlockCount) {
        nSubsidy *= 2;
    }

    return  nSubsidy + nFees;
}

