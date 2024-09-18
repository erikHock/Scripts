using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyHurtParticlesHandler : MonoBehaviour
{
    [SerializeField] ParticleSystem _particles;

    private void OnEnable()
    {
        _particles.gameObject.SetActive(false);
        BulletDamage.OnBulletDamagePosition += PlayParticles;
    }

    private void OnDisable()
    {
        BulletDamage.OnBulletDamagePosition -= PlayParticles;
    }

    private void PlayParticles(Vector3 position)
    {
        float offset = 10f;
        _particles.gameObject.SetActive(true);
        _particles.gameObject.transform.position = position;
        
        _particles.transform.forward = (position * 20f);

        if (!_particles.isPlaying)
        {
            _particles.Play();
        }
        
        
    }
}
