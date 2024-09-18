using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using UnityEngine.UI;
using System;

public class CardSOHolder : MonoBehaviour
{
    [SerializeField] private CardSO _cardSO;
    [SerializeField] private TextMeshProUGUI _header;
    [SerializeField] private TextMeshProUGUI _details;
    [SerializeField] private Button _button;

    public static Action<CardSO> OnCardChoosed;
    public CardSO GetScriptableObject()
    {
        if (_cardSO != null)
        {
            return _cardSO;
        }
        return null;
        Debug.LogError($"CardSOHolder:{_cardSO} is null");
    }

    public void SetScriptableObject(CardSO cardSO)
    {
        _cardSO = cardSO;
    }

    public void InitVisual()
    {
        if (_cardSO == null)
        {
            Debug.LogError($"CardSOHolder:{_cardSO} is null");
            return;
        }

        AssignColor();
        AssignText();
        AssignButton();
    }

    private void AssignColor()
    {
        TryGetComponent<Image>(out Image cardImage);

        if (cardImage != null)
        {
            switch (_cardSO.rarity)
            {
                case 1:
                    cardImage.color = Color.green;
                    break;

                case 2:
                    cardImage.color = Color.yellow;
                    break;

                case 3:
                    cardImage.color = Color.red;
                    break;
            }
        }
    }

    private void AssignText()
    {
        _header.text = _cardSO.header;
        _details.text = _cardSO.details;
    }

    private void AssignButton()
    {
        _button.onClick.AddListener(() => { PlayerStateMachine.Instance.ChangePlayerState(PlayerStates.Attack);
                                            OnCardChoosed?.Invoke(_cardSO);
                                           } );
    }


}
