// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#include "Units.h"

#include <QtCore/QObject>

QString unitsToString(Units units) {
  QString unitsStr;
  switch (units) {
    case PIXELS:
      unitsStr = "px";
      break;
    case MILLIMETRES:
      unitsStr = "mm";
      break;
    case CENTIMETRES:
      unitsStr = "cm";
      break;
    case INCHES:
      unitsStr = "in";
      break;
  }
  return unitsStr;
}

Units unitsFromString(const QString& string) {
  if (string == "px") {
    return PIXELS;
  } else if (string == "cm") {
    return CENTIMETRES;
  } else if (string == "in") {
    return INCHES;
  } else {
    return MILLIMETRES;
  }
}

QString unitsToLocalizedString(Units units) {
  QString unitsStr;
  switch (units) {
    case PIXELS:
      unitsStr = QObject::tr("px");
      break;
    case MILLIMETRES:
      unitsStr = QObject::tr("mm");
      break;
    case CENTIMETRES:
      unitsStr = QObject::tr("cm");
      break;
    case INCHES:
      unitsStr = QObject::tr("in");
      break;
  }
  return unitsStr;
}