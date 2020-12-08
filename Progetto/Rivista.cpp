#include "Rivista.h"

Rivista::Rivista() : Base(), editore(""), volume(0) {}

QString Rivista::getEditore() const { return editore; }

int Rivista::getVolume() const { return volume; }

void Rivista::setEditore(QString editor) { editore = editor; }

void Rivista::setVolume(int vol) { volume = vol; }


