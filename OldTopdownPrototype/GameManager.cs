using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance;

    public static Action<GameStates> OnGameStateChanged;
    private GameStates _currentState;

    private void Awake()
    {
        Instance = this;
    }

    private void Start()
    {
        ChangeGameState(GameStates.GameLoop);
    }

    public void ChangeGameState(GameStates state)
    {
        _currentState = state;

        switch (state)
        {
            case GameStates.GameLoop:
                StartTime();
                break;

            case GameStates.GamePaused:
                StopTime();
                break;

            case GameStates.GameEnd:
                StartTime();
                break;
        }

        OnGameStateChanged?.Invoke(state);
    }

    private void StopTime()
    {
        Time.timeScale = 0;
    }

    private void StartTime()
    {
        Time.timeScale = 1;
    }
}

public enum GameStates
{
    GameLoop,
    GamePaused,
    GameEnd
}
