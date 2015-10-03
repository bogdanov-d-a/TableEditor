#include "documentstate.h"

DocumentState::DocumentState()
{
    setDataChanged(false);
}

void DocumentState::newFile()
{
    saveUnsavedData();
    setDataChanged(false);
    m_filePath.clear();
    loadData();
}

void DocumentState::open()
{
    saveUnsavedData();
    setDataChanged(false);
    m_filePath = "input.json";
    loadData(m_filePath);
}

void DocumentState::save()
{
    saveImpl(false);
}

void DocumentState::saveAs()
{
    saveImpl(true);
}

void DocumentState::modified()
{
    setDataChanged(true);
}

void DocumentState::saveImpl(bool forcePrompt)
{
    if (m_filePath.size() == 0 || forcePrompt)
        m_filePath = "output.json";

    saveData(m_filePath);
    setDataChanged(false);
}

void DocumentState::saveUnsavedData()
{
    if (m_dataChanged && true)
    {
        saveImpl(false);
    }
}

void DocumentState::setDataChanged(bool dataChanged)
{
    m_dataChanged = dataChanged;
    canSaveChanged(m_dataChanged);
}
