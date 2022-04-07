/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

//    m_dataManager = new DataManagerDb;

const auto STUDENTS_SQL =  QLatin1String(R"(
        create table students(zkh varchar(20), name varchar(20),  gender integer, zxdm varchar(20), zxmc varchar(20), id varchar(30)))");

const auto SCHOOLS_SQL =  QLatin1String(R"(
        create table schools(checked integer, zxdm varchar(10) unique, zxmc varchar(15), downloaded integer))");

const auto EXAMPROJECTS_SQL =  QLatin1String(R"(
        create table examprojects(name varchar(15), type varchar(15), unit varchar(15), value varchar(20)))");

const auto INSERT_EXAMPROJECT_SQL = QLatin1String(R"(
        insert into examprojects(name, type, unit, value)
                          values(?, ?, ?, ?))");

const auto INSERT_STUDENT_SQL = QLatin1String(R"(
        insert into students(id, zkh, name, gender, zxdm, zxmc)
                          values(?, ?, ?, ?, ?, ?))");

const auto INSERT_SCHOOL_SQL = QLatin1String(R"(
        insert into schools(checked, zxdm, zxmc, downloaded)
                          values(?, ?, ?, ?))");

const auto SCORES_SQL = QLatin1String(R"(
        create table scores(zkh varchar(20),
        name varchar(10),
        gender interger,
        project varchar(10),
        firstScore integer,
        secondScore integer,
        thirdScore integer,
        midStopFirst integer,
        midStopSecond integer,
        midStopThird integer,
        examTime varchar(40),
        uploadStatus integer,
        errorMsg varchar(40),
        onSiteVideo varchar(40)))");

const auto INSERT_SCORE_SQL = QLatin1String(R"(
        insert into scores(zkh, name, gender, project, firstScore, secondScore, thirdScore,
                           midStopFirst, midStopSecond, midStopThird, examTime, uploadStatus, errorMsg, onSiteVideo)
                           values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?))");


void initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open()) {
        qDebug() << __func__ << db.lastError().text();
    } else {
        qDebug() << __func__ << "database open successfully";
    }

    QStringList tables = db.tables();
    qDebug() << __func__ <<  __LINE__ << tables;
    if (tables.contains("studetns", Qt::CaseInsensitive)
            && tables.contains("schools", Qt::CaseInsensitive)
            && tables.contains("scores", Qt::CaseInsensitive)
            && tables.contains("examprojects", Qt::CaseInsensitive)) {
        qDebug() << db.lastError().text();
        return;
    }

    QSqlQuery q;
    if (!q.exec(SCHOOLS_SQL)) {
        //        qDebug() << q.exec("insert into schools values(1, 2, '1234', 'abc', 0)");
        //        qDebug() << q.exec("insert into schools values(3, 3, '1234', 'abc', 0)");
        //        qDebug() << q.exec("insert into schools values(4, 4, '1234', 'abc', 0)");
        qDebug() << __func__ <<  __LINE__ << q.lastError().text();
    }

    if (!q.exec(EXAMPROJECTS_SQL))
        qDebug() << __func__ << __LINE__ << q.lastError().text();
    if (!q.exec(STUDENTS_SQL))
        qDebug() << __func__ << __LINE__ << q.lastError().text();
    if (!q.exec(SCORES_SQL))
        qDebug() << __func__ << __LINE__ << q.lastError().text();


}
#endif
