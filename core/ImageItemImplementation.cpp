/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ImageItemImplementation.h"

ImageItemImplementation::ImageItemImplementation(const ImageItemImplementation &original) :
  _path{original._path},
  _value{original._value}
{
}

ImageItemImplementation::ImageItemImplementation(QString path, QString value) :
  _path{path},
  _value{value}
{
}

QVariant ImageItemImplementation::data(int role) const
{
  switch (role) {
  case PathRole:
    return _path;
  case ValueRole:
    return _value;
  }

  return {};
}

QString ImageItemImplementation::path() const
{
  return _path;
}

QString ImageItemImplementation::value() const
{
  return _value;
}
