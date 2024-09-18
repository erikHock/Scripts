using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;

public class LootManager : MonoBehaviour
{
    [SerializeField] private Transform _cardPanel;
    [SerializeField] private GameObject _cardPrefab;

    private Dictionary<CardSO,GameObject> _spawnedCards = new Dictionary<CardSO,GameObject>();
    private List<CardSO> _cards = new List<CardSO>();
    private int _maxCardsCount = 3;

    private void Awake()
    {
        _cards = Resources.LoadAll<CardSO>("ScriptableObjects/CardSO").ToList();
        CanvasActivate(false);
    }
    private void OnEnable()
    {
        PlayerStateMachine.Instance.OnStateChange += ShowLootTable;
        PlayerStateMachine.Instance.OnInteractEnd += HideLootTable;
    }

    private void OnDisable()
    {
        PlayerStateMachine.Instance.OnStateChange -= ShowLootTable;
        PlayerStateMachine.Instance.OnInteractEnd -= HideLootTable;
    }

    private void CanvasActivate(bool b)
    {
        _cardPanel.gameObject.SetActive(b);
    }
    
    private void ShowLootTable(PlayerStates state)
    {
        if (state != PlayerStates.Interact) { return; }

        CanvasActivate(true);

        _spawnedCards.Clear();

        for (int i = 0; i < _maxCardsCount; i++)
        {
            int randomNumber = Random.Range(0, _cards.Count);

            var spawnedObj = Instantiate(_cardPrefab);
            var spawnedCard = Instantiate(_cards[randomNumber]);

            var cardHolder = spawnedObj.GetComponent<CardSOHolder>();
            cardHolder.SetScriptableObject(spawnedCard);
            cardHolder.InitVisual();

            spawnedObj.transform.SetParent(_cardPanel);

            _spawnedCards.Add(spawnedCard, spawnedObj);
            
        }
    }

    private void HideLootTable()
    {
        if (_spawnedCards.Count != 0)
        {
            foreach (var kvp in _spawnedCards)
            {
                Destroy(kvp.Value.gameObject);
            }
            _spawnedCards.Clear();
        }

        CanvasActivate(false);
    }
    
}
