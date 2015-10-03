#ifndef DOCUMENTSTATE_H
#define DOCUMENTSTATE_H

#include <QObject>

class DocumentState : public QObject
{
    Q_OBJECT
public:
    DocumentState();
    void newFile();
    void open();
    void save();
    void saveAs();

public slots:
    void modified();

signals:
    void loadData(QString const& path = QString());
    void saveData(QString const& path);
    void canSaveChanged(bool canSave);

private:
    void saveImpl(bool forcePrompt);
    void saveUnsavedData();
    void setDataChanged(bool dataChanged);

    bool m_dataChanged;
    QString m_filePath;
};

#endif // DOCUMENTSTATE_H
