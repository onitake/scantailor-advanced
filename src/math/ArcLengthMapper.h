// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#ifndef SCANTAILOR_MATH_ARCLENGTHMAPPER_H_
#define SCANTAILOR_MATH_ARCLENGTHMAPPER_H_

#include <vector>

/**
 * \brief Maps from x to arclen(f(x)) and back.
 *
 * Suppose we have a discrete function where we only know its
 * values for a given set of arguments.  This class provides a way
 * to calculate the both arc length corresponding to an arbitrary x,
 * and x corresponding to an arbitrary arc length.
 * We consider the arc length between two adjacent samples
 * to be monotonously increasing, that is we consider adjacent samples
 * to be connected by straight lines.
 */
class ArcLengthMapper {
  // Member-wise copying is OK.
 public:
  class Hint {
    friend class ArcLengthMapper;

   public:
    Hint();

   private:
    void update(int newSegment);

    int m_lastSegment;
    int m_direction;
  };


  ArcLengthMapper();

  /**
   * \brief Adds an x -> f(x) sample.
   *
   * Note that x value of every sample has to be bigger than that
   * of the previous one.
   */
  void addSample(double x, double fx);

  /**
   * \brief Returns the total arc length from the first to the last sample.
   */
  double totalArcLength() const;

  /**
   * \brief Scales arc lengths at every sample so that the
   *        total arc length becomes equal to the given value.
   *
   * Obviously, this should be done after all samples have been added.
   * After calling this function, totalArcLength() will be returning
   * the new value.
   */
  void normalizeRange(double totalArcLen);

  /**
   * \brief Maps from arc length to the corresponding function argument.
   *
   * This works even for arc length beyond the first or last samples.
   * When interpolation is impossible, the closest sample is returned.
   * If no samples are present, zero is returned.  Providing the same
   * hint on consecutive calls to this function improves performance.
   */
  double arcLenToX(double arcLen, Hint& hint) const;

  double xToArcLen(double x, Hint& hint) const;

 private:
  struct Sample {
    double x;
    double arcLen;

    Sample(double x, double arcLen) : x(x), arcLen(arcLen) {}
  };

  bool checkSegmentForArcLen(double arcLen, int segment) const;

  bool checkSegmentForX(double x, int segment) const;

  double interpolateArcLenInSegment(double arcLen, int segment) const;

  double interpolateXInSegment(double x, int segment) const;

  std::vector<Sample> m_samples;
  double m_prevFX;
};


#endif  // ifndef SCANTAILOR_MATH_ARCLENGTHMAPPER_H_
