#include "tools/cabana/settings.h"

#include <QDialogButtonBox>
#include <QDir>
#include <QFormLayout>
#include <QSettings>

// Settings
Settings settings;

Settings::Settings() {
  load();
}

void Settings::save() {
  QSettings s("settings", QSettings::IniFormat);
  s.setValue("fps", fps);
  s.setValue("max_cached_minutes", max_cached_minutes);
  s.setValue("chart_height", chart_height);
  s.setValue("chart_range", chart_range);
  s.setValue("chart_column_count", chart_column_count);
  s.setValue("last_dir", last_dir);
  s.setValue("window_state", window_state);
  s.setValue("geometry", geometry);
  s.setValue("video_splitter_state", video_splitter_state);
}

void Settings::load() {
  QSettings s("settings", QSettings::IniFormat);
  fps = s.value("fps", 10).toInt();
  max_cached_minutes = s.value("max_cached_minutes", 5).toInt();
  chart_height = s.value("chart_height", 200).toInt();
  chart_range = s.value("chart_range", 3 * 60).toInt();
  chart_column_count = s.value("chart_column_count", 1).toInt();
  last_dir = s.value("last_dir", QDir::homePath()).toString();
  window_state = s.value("window_state").toByteArray();
  geometry = s.value("geometry").toByteArray();
  video_splitter_state = s.value("video_splitter_state").toByteArray();
}

// SettingsDlg

SettingsDlg::SettingsDlg(QWidget *parent) : QDialog(parent) {
  setWindowTitle(tr("Settings"));
  QFormLayout *form_layout = new QFormLayout(this);

  fps = new QSpinBox(this);
  fps->setRange(10, 100);
  fps->setSingleStep(10);
  fps->setValue(settings.fps);
  form_layout->addRow("FPS", fps);

  cached_minutes = new QSpinBox(this);
  cached_minutes->setRange(5, 60);
  cached_minutes->setSingleStep(1);
  cached_minutes->setValue(settings.max_cached_minutes);
  form_layout->addRow(tr("Max Cached Minutes"), cached_minutes);

  chart_height = new QSpinBox(this);
  chart_height->setRange(100, 500);
  chart_height->setSingleStep(10);
  chart_height->setValue(settings.chart_height);
  form_layout->addRow(tr("Chart Height"), chart_height);

  auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  form_layout->addRow(buttonBox);

  setFixedWidth(360);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDlg::save);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void SettingsDlg::save() {
  settings.fps = fps->value();
  settings.max_cached_minutes = cached_minutes->value();
  settings.chart_height = chart_height->value();
  settings.save();
  accept();
  emit settings.changed();
}
