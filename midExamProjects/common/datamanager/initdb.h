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
        create table students(id integer primary key, zkh varchar, name varchar,  gender int, zxdm vchar, zxmc vchar))");

const auto SCHOOLS_SQL =  QLatin1String(R"(
        create table schools(checked integer, zxdm varchar, zxmc varchar, downloaded integer))");


const auto INSERT_STUDENT_SQL = QLatin1String(R"(
        insert into students(zkh, year, name, gender, zxdm, zxmc)
                          values(?, ?, ?, ?, ?, ?))");

const auto INSERT_SCHOOL_SQL = QLatin1String(R"(
        insert into schools(checked, zxdm, zxmc, downloaded)
                          values(?, ?, ?, ?))");

const auto SCORES_SQL = QLatin1String(R"(
        create table scores(id integer primary key,
        zkh varchar,
        name varchar,
        gender interger,
        project varchar
        firstScore varchar,
        secondScore varchar,
        thirdScore varchar,
        examTime varchar,
        uploadStatus int,
        errorMsg varchar,
        onSiteVideo varchar))");

const auto INSERT_SCORE_SQL = QLatin1String(R"(
        insert into scores(zkh, name, gender, project, firstScore, secondScore, thirdScore,
                           examTime, uploadStatus, errorMsg, onSiteVide)
                           values(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?))");


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
    if (tables.contains("studetns", Qt::CaseInsensitive)
            && tables.contains("schools", Qt::CaseInsensitive)
            && tables.contains("scores", Qt::CaseInsensitive)) {
        qDebug() << db.lastError().text();
        return;
    }

    QSqlQuery q;
    if (!q.exec(SCHOOLS_SQL)) {
        //        qDebug() << q.exec("insert into schools values(1, 2, '1234', 'abc', 0)");
        //        qDebug() << q.exec("insert into schools values(3, 3, '1234', 'abc', 0)");
        //        qDebug() << q.exec("insert into schools values(4, 4, '1234', 'abc', 0)");
        qDebug() << __LINE__ << q.lastError().text();
    }

    if (!q.exec(STUDENTS_SQL))
        qDebug() << __LINE__ << q.lastError().text();
    if (!q.exec(SCORES_SQL))
        qDebug() << __LINE__ << q.lastError().text();

}
#endif
