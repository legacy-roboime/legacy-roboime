#ifndef GRAPHICALINTELLIGENCE_H
#define GRAPHICALINTELLIGENCE_H

#include <QtGui/QMainWindow>
#include "ui_GraphicalIntelligence.h"

#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QThread>
#include <map>

#include "Team.h"
#include "Stage.h"
#include "Commander.h"
#include "Updater.h"
#include "Skill.h"
#include "Tactic.h"
#include "Play.h"
#include "config.h"

using namespace LibIntelligence;

class GraphicalIntelligence : public QMainWindow
{
	friend struct IntelligenceCli;
	Q_OBJECT

public:
	GraphicalIntelligence(QWidget *parent = 0, Qt::WFlags flags = 0);
	~GraphicalIntelligence();

	// STP utils
	map<string, Plays::Play*> play;
	map<string, Tactics::Tactic*> tactic;
	map<string, Skills::Skill*> skill;
	enum {NONE, SKILL, TACTIC, PLAY, CONTROLLER} mode;
	int controlled;//tirar quando o controller for para o time inteiro

public slots:
	void update();

private slots:
	void updateValues();
	void on_btnIntStart_clicked();
	void on_btnIntStop_clicked();

private:	
	Ui::GraphicalIntelligenceClass ui;
	QHash<char,QString> refereeFull;
	int goalsBlue, goalsYellow;

	// Basic objects
	map<string, Team*> team;
	map<string, Robot*> robot;
	map<string, Stage*> stage;

	// Interface utils
	map<string, Commander*> commander;
	map<string, Updater*> updater;
	bool useSimulation;
	void resetPatterns();

	QTimer* timer;
	QThread* cli;
	QMutex mutex;
};

#endif // GRAPHICALINTELLIGENCE_H