using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HealthBar : MonoBehaviour
{
    [SerializeField] private Gradient _gradient;
    [SerializeField] private Image _fillImage;

    private Slider _slider;

    private void Awake()
    {
        _slider = GetComponent<Slider>();
        _fillImage.color = _gradient.Evaluate(_slider.normalizedValue);
    }

    public void SetSliderMaxValue(float value)
    {
        _slider.maxValue = value / 100;
        _fillImage.color = _gradient.Evaluate(_slider.normalizedValue);
    }

    public void SetSliderCurrentValue(float value)
    {
        _slider.value = value / 100;
        _fillImage.color = _gradient.Evaluate(_slider.normalizedValue);
    }
}
