using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChestVisual : MonoBehaviour
{
    [SerializeField] private ParticleSystem _particleSystem;

    private void OnEnable()
    {
        PlayerStateMachine.Instance.OnInteractEnd += DisableParticles;
    }

    private void OnDisable()
    {
        PlayerStateMachine.Instance.OnInteractEnd -= DisableParticles;
    }

    private void DisableParticles()
    {
        _particleSystem.gameObject.SetActive(false);
    }


}
